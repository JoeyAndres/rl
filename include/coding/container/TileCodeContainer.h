/**
 * rl - Reinforcement Learning
 * Copyright (C) 2016  Joey Andres<yeojserdna@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef ENABLE_DB

#include <cassandra.h>
#include <string>
#include <memory>
#include <tuple>
#include <exception>
#include <vector>

#include "../../declares.h"
#include "../../utility/CRUDInterface.h"
#include "TileCodeContainerSegment.h"

using std::string;
using std::shared_ptr;
using std::tuple;
using std::exception;
using std::vector;

namespace rl {
namespace coding {

/*!\class TileCodeContainer
 * \brief Wraps TileCodeContainer.
 * \tparam ID_CHARS The id of the TileCodeContainer.
 *
 * Container type for TileCode weight vectors.
 */
template <char... ID_CHARS>
class TileCodeContainer;

/*!\class spTileCodeContainer
 * \brief Wraps TileCodeContainer.
 * \tparam ID_CHARS
 */
template <char... ID_CHARS>
using spTileCodeContainer = shared_ptr<TileCodeContainer<ID_CHARS...>>;

using TileCodeContainerAllocator = std::allocator<TileCodeContainerCell>;

template <char... ID_CHARS>
class TileCodeContainer :
  public utility::CRUDInterface {
 public:
  typedef TileCodeContainerAllocator allocator_type;
  typedef typename TileCodeContainerAllocator::value_type value_type;

  // We did not use the allocator here to avoid saving this in ram, defeating
  // the purpose of using db.
  typedef TileCodeContainerCell reference;
  typedef TileCodeContainerCell const_reference;

  typedef typename TileCodeContainerAllocator::difference_type difference_type;
  typedef typename TileCodeContainerAllocator::size_type size_type;

 public:
  /**
   * Creates an entry in db if not exist yet, otherwise
   * retrieves the existing db.
   *
   * @param size Number of weight vector in this container.
   * @param iniitialValue Initial value.
   */
  TileCodeContainer(size_t size, FLOAT initialValue);
  TileCodeContainer();

  /**
   * @return true if already in db.
   */
  bool created() const;

  void create() override;
  void read() override;
  void update() override;
  void delete2() override;

  /**
   * @return ID in string.
   */
  string getID() const;

  /**
   * @return segment count.
   */
  size_t getSegmentCount() const;

  /**
   * @return Array of TileCodeContainerSegment.
   */
  std::vector<spTileCodeContainerSegment> getSegments() const;

  /**
   * @return TileCodeContainerCell entry in db.
   */
  TileCodeContainerCell operator[](size_t i) const;
  TileCodeContainerCell at(size_t i) const;

 protected:
  void _deleteAllSegments();

 public:
  /**
   * Initialize the underlying database for TileCodeContainer.
   */
  static void createSchema();

  /**
   * Destroys the underlying database for TileCodeContainer.
   */
  static void destroySchema();

 protected:
  static void _createTileContainerTable();

  static string _insertTileCodeContainer(size_t size, FLOAT initialValue);

  static tuple<string, size_t, FLOAT>  _getTileContainer(string uuid)
  throw(exception);

 protected:
  size_t _size;
  FLOAT _initialValue = 0.0F;
  vector<spTileCodeContainerSegment> _segments;
};

template <char... ID_CHARS>
TileCodeContainer<ID_CHARS...>::TileCodeContainer(
  size_t size, FLOAT initialValue) :
  _size(size),
  _initialValue(initialValue) {
  db::initialize();
  TileCodeContainer::createSchema();

  if (created()) {
    read();
  } else {
    create();
  }
}

template <char... ID_CHARS>
TileCodeContainer<ID_CHARS...>::TileCodeContainer() {
  db::initialize();
  TileCodeContainer::createSchema();
  read();
}

template <char... ID_CHARS>
bool TileCodeContainer<ID_CHARS...>::created() const {
  string stmtStr = ""
    "SELECT COUNT(*) as count\n"
    "FROM rl.tilecodecontainer\n"
    "WHERE id='" + getID() + "';\n";

  CassStatement *stmt = cass_statement_new(stmtStr.c_str(), 0);

  CassFuture *resultFuture =
    cass_session_execute(db::session, stmt);

  const CassResult *result = cass_future_get_result(resultFuture);

  // This will block until the query has finished.
  CassError rc = cass_future_error_code(resultFuture);

  // If there was an error then the result won't be available.
  if (result == NULL) {
    /* Handle error */
    printf("Query result: %s\n", cass_error_desc(rc));
    cass_future_free(resultFuture);
    throw "Query failed.";
  }

  // The future can be freed immediately after getting the result object.
  cass_future_free(resultFuture);

  // This can be used to retrieve on the first row of the result.
  const CassRow *row = cass_result_first_row(result);

  cass_int64_t size;
  // Get the column value of "size" by name.
  cass_value_get_int64(cass_row_get_column_by_name(row, "count"), &size);

  // This will free the result as well as the string pointed to by 'key'.
  cass_result_free(result);

  return size;
}

template <char... ID_CHARS>
void TileCodeContainer<ID_CHARS...>::create() {
  CassStatement* stmt =
    cass_statement_new(db::InsertTileCodeContainer.c_str(), 3);

  // Bind the values using the indices of the bind variables.
  cass_statement_bind_string(stmt, 0, getID().c_str());
  cass_statement_bind_int64(stmt, 1, _size);
  cass_statement_bind_double(stmt, 2, _initialValue);

  CassFuture* queryFuture = cass_session_execute(
    db::session, stmt);

  // Statement objects can be freed immediately after being executed.
  cass_statement_free(stmt);

  // This will block until the query has finished.
  CassError rc = cass_future_error_code(queryFuture);

  if (rc != CASS_OK) {
    printf("Query result: %s\n", cass_error_desc(rc));
    throw "Error creating TileCodeContainer";
  }

  cass_future_free(queryFuture);

  // Create the segments.
  size_t segmentCount = getSegmentCount();
#ifdef DEBUG
  std::cout << "Segment count: " << segmentCount << std::endl;
#endif
  for (size_t i = 0; i < segmentCount; i++) {
    TileCodeContainerSegment tccs(getID(), SEGMENT_SIZE, i);
  }

  _segments = getSegments();
}

template <char... ID_CHARS>
void TileCodeContainer<ID_CHARS...>::read() {
  string stmtStr = ""
    "SELECT size, initialValue\n"
    "FROM rl.tilecodecontainer\n"
    "WHERE id='" + getID() + "';\n";
  CassStatement *stmt = cass_statement_new(stmtStr.c_str(), 0);

  CassFuture *resultFuture =
    cass_session_execute(db::session, stmt);

  const CassResult *result = cass_future_get_result(resultFuture);

  // This will block until the query has finished.
  CassError rc = cass_future_error_code(resultFuture);

  // If there was an error then the result won't be available.
  if (result == NULL) {
    /* Handle error */
    printf("Query result: %s\n", cass_error_desc(rc));
    cass_future_free(resultFuture);
    throw "Query failed.";
  }

  // The future can be freed immediately after getting the result object.
  cass_future_free(resultFuture);

  // This can be used to retrieve on the first row of the result.
  const CassRow *row = cass_result_first_row(result);

  cass_int64_t size;
  // Get the column value of "size" by name.
  cass_value_get_int64(cass_row_get_column_by_name(row, "size"), &size);

  cass_double_t initialValue;
  // Get the column value of "initialValue" by name.
  cass_value_get_double(
    cass_row_get_column_by_name(row, "initialValue"), &initialValue);

  // This will free the result as well as the string pointed to by 'key'.
  cass_result_free(result);

  this->_size = size;
  this->_initialValue = initialValue;
  _segments = getSegments();
}

template <char... ID_CHARS>
void TileCodeContainer<ID_CHARS...>::update() {
}

template <char... ID_CHARS>
void TileCodeContainer<ID_CHARS...>::delete2() {
  this->_deleteAllSegments();

  string stmtStr = ""
    "DELETE FROM rl.tilecodecontainer\n"
    "WHERE id='" + getID() + "';\n";
  CassStatement* stmt = cass_statement_new(stmtStr.c_str(), 0);

  CassFuture* resultFuture =
    cass_session_execute(db::session, stmt);

  // This will block until the query has finished.
  CassError rc = cass_future_error_code(resultFuture);

  const CassResult* result = cass_future_get_result(resultFuture);

  // If there was an error then the result won't be available.
  if (result == NULL) {
    /* Handle error */
    printf("Query result: %s\n", cass_error_desc(rc));
    cass_future_free(resultFuture);
    throw "Query failed.";
  }

  cass_statement_free(stmt);
  cass_future_free(resultFuture);
}

template <char... ID_CHARS>
string TileCodeContainer<ID_CHARS...>::getID() const {
  std::string str{ { ID_CHARS... } };
  return str;
}

template <char... ID_CHARS>
size_t TileCodeContainer<ID_CHARS...>::getSegmentCount() const {
  return std::ceil(
    static_cast<FLOAT>(_size) / static_cast<FLOAT>(rl::SEGMENT_SIZE));
}

template <char... ID_CHARS>
vector<spTileCodeContainerSegment>
TileCodeContainer<ID_CHARS...>::getSegments() const {
  vector<spTileCodeContainerSegment> tileCodeContainerSegments;
  string stmtStr = ""
    "SELECT tileCodeContainerId, segmentIndex\n"
    "FROM rl.tilecodecontainersegment\n"
    "WHERE tileCodeContainerId='" + getID() + "'\n"
    "ORDER BY segmentIndex ASC\n"
    "ALLOW FILTERING;\n";

  CassStatement* stmt = cass_statement_new(stmtStr.c_str(), 0);

  CassFuture* resultFuture =
    cass_session_execute(db::session, stmt);

  // This will block until the query has finished.
  CassError rc = cass_future_error_code(resultFuture);

  const CassResult* result = cass_future_get_result(resultFuture);

  // If there was an error then the result won't be available.
  if (result == NULL) {
    /* Handle error */
    printf("Query result: %s\n", cass_error_desc(rc));
    cass_future_free(resultFuture);
    throw "Query failed.";
  }

  CassIterator* iterator = cass_iterator_from_result(result);

  while (cass_iterator_next(iterator)) {
    const CassRow* row = cass_iterator_get_row(iterator);
    // Retrieve and use values from the row.

    cass_int64_t segmentIndex;
    cass_value_get_int64(
      cass_row_get_column_by_name(row, "segmentIndex"), &segmentIndex);

    tileCodeContainerSegments.push_back(
      spTileCodeContainerSegment(
        new TileCodeContainerSegment(getID(), segmentIndex)));
  }

  // This will free the result as well as the string pointed to by 'key'.
  cass_iterator_free(iterator);
  cass_result_free(result);

  return tileCodeContainerSegments;
}

template <char... ID_CHARS>
void TileCodeContainer<ID_CHARS...>::createSchema() {
  TileCodeContainer::_createTileContainerTable();
}

template <char... ID_CHARS>
void TileCodeContainer<ID_CHARS...>::_createTileContainerTable() {
  db::executeStatement(db::TileCodeContainer.c_str());
}

template <char... ID_CHARS>
void TileCodeContainer<ID_CHARS...>::_deleteAllSegments() {
  for (auto segment : this->getSegments()) {
    segment->delete2();
  }
}

template <char... ID_CHARS>
TileCodeContainerCell
TileCodeContainer<ID_CHARS...>::operator[](size_t i) const {
  return this->at(i);
}

template <char... ID_CHARS>
TileCodeContainerCell TileCodeContainer<ID_CHARS...>::at(size_t i) const {
  size_t segmentIndex = i / SEGMENT_SIZE;
  size_t innerSegmentIndex = i % SEGMENT_SIZE;
  return _segments[segmentIndex]->at(innerSegmentIndex);
}

}  // namespace coding
}  // namespace rl

#endif  // #ifdef ENABLE_DB
