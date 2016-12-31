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

#include <cassandra.h>
#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>

#include "declares.h"
#include "db/definition.h"
#include "db/manipulation.h"
#include "db/utility.h"
#include "coding/TileCodeContainer.h"
#include "coding/TileCodeContainerSegment.h"

using std::vector;

namespace rl {
namespace coding {

TileCodeContainer::TileCodeContainer(size_t size, FLOAT initialValue) :
  _size(size),
  _initialValue(initialValue),
  _id("") {
  db::initialize();
  TileCodeContainer::createSchema();
  create();
}

TileCodeContainer::TileCodeContainer(const string& id) : _id(id) {
  db::initialize();
  TileCodeContainer::createSchema();
  read();
}

void TileCodeContainer::create() {
  if (_inserted) {
    return;
  }

  _id = TileCodeContainer::_insertTileCodeContainer(_size, _initialValue);
  _setInserted(true);

  // Create the segments.
  size_t segmentCount = getSegmentCount();
#ifdef DEBUG
  std::cout << "Segment count: " << segmentCount << std::endl;
#endif
  for (size_t i = 0; i < segmentCount; i++) {
    TileCodeContainerSegment tccs(_id, SEGMENT_SIZE, i);
  }

  _segments = getSegments();
}

void TileCodeContainer::read() {
  if (_inserted) {
    return;
  }

  // Throws exception if _id is invalid.
  auto paramTuple = TileCodeContainer::_getTileContainer(_id);
  this->_id = std::get<0>(paramTuple);
  this->_size = std::get<1>(paramTuple);
  this->_initialValue = std::get<2>(paramTuple);

  _segments = getSegments();
  _setInserted(true);
}

void TileCodeContainer::update() {
}

void TileCodeContainer::delete2() {
  if (!_inserted) {
    return;
  }

  this->_deleteAllSegments();

  string stmtStr = ""
    "DELETE FROM rl.tilecodecontainer\n"
    "WHERE id = " + _id + ";\n";
  CassStatement* stmt = cass_statement_new(stmtStr.c_str(), 0);

  CassFuture* resultFuture =
    cass_session_execute(db::session, stmt);

  const CassResult* result = cass_future_get_result(resultFuture);

  // If there was an error then the result won't be available.
  if (result == NULL) {
    /* Handle error */
    throw "Query failed.";
  }

  cass_statement_free(stmt);
  cass_future_free(resultFuture);

  _setInserted(false);
}

string TileCodeContainer::getID() const {
  return _id;
}

size_t TileCodeContainer::getSegmentCount() const {
  return std::ceil(
    static_cast<FLOAT>(_size) / static_cast<FLOAT>(rl::SEGMENT_SIZE));
}

void TileCodeContainer::_setInserted(bool inserted) {
  _inserted = inserted;

  if (!inserted) {
    _id = "";
  }
}

vector<spTileCodeContainerSegment>
TileCodeContainer::getSegments() const {
  vector<spTileCodeContainerSegment> tileCodeContainerSegments;

  string stmtStr = ""
    "SELECT tileCodeContainerId, segmentIndex \n"
    "FROM rl.tilecodecontainersegment\n"
    "WHERE tileCodeContainerId = " + _id + "\n"
    "ORDER BY segmentIndex ASC\n"
    "ALLOW FILTERING;\n";

  CassStatement* stmt = cass_statement_new(stmtStr.c_str(), 0);

  CassFuture* resultFuture =
    cass_session_execute(db::session, stmt);

  const CassResult* result = cass_future_get_result(resultFuture);

  // If there was an error then the result won't be available.
  if (result == NULL) {
    /* Handle error */
    cass_future_free(resultFuture);
    throw "Query failed.";
  }

  CassIterator* iterator = cass_iterator_from_result(result);

  while (cass_iterator_next(iterator)) {
    const CassRow* row = cass_iterator_get_row(iterator);
    // Retrieve and use values from the row.

    CassUuid tileCodeContainerSegmentId;
    cass_value_get_uuid(
      cass_row_get_column_by_name(row, "tileCodeContainerId"),
      &tileCodeContainerSegmentId);
    char tileCodeContainerSegmentIdStr[CASS_UUID_STRING_LENGTH];
    cass_uuid_string(
      tileCodeContainerSegmentId, tileCodeContainerSegmentIdStr);

    cass_int64_t segmentIndex;
    cass_value_get_int64(
      cass_row_get_column_by_name(row, "segmentIndex"), &segmentIndex);

    tileCodeContainerSegments.push_back(
      spTileCodeContainerSegment(
        new TileCodeContainerSegment(
          tileCodeContainerSegmentIdStr, segmentIndex)));
  }

  // This will free the result as well as the string pointed to by 'key'.
  cass_iterator_free(iterator);
  cass_result_free(result);

  return tileCodeContainerSegments;
}

void TileCodeContainer::createSchema() {
  TileCodeContainer::_createTileContainerTable();
}

void TileCodeContainer::_createTileContainerTable() {
  db::executeStatement(db::TileCodeContainer.c_str());
}

void TileCodeContainer::_deleteAllSegments() {
  for (auto segment : this->getSegments()) {
    segment->delete2();
  }
}

string TileCodeContainer::_insertTileCodeContainer(
  size_t size, FLOAT initialValue){
  CassStatement* stmt =
    cass_statement_new(db::InsertTileCodeContainer.c_str(), 3);

  // Generate id.
  CassUuid id = db::genUuid();

  // Bind the values using the indices of the bind variables.
  cass_statement_bind_uuid(stmt, 0, id);
  cass_statement_bind_int64(stmt, 1, size);
  cass_statement_bind_double(stmt, 2, initialValue);

  CassFuture* queryFuture = cass_session_execute(
    db::session, stmt);

  // Statement objects can be freed immediately after being executed.
  cass_statement_free(stmt);

  // This will block until the query has finished.
  CassError rc = cass_future_error_code(queryFuture);

  if (rc != CASS_OK) {
    printf("Query result: %s\n", cass_error_desc(rc));
  }


  cass_future_free(queryFuture);

  char idStr[CASS_UUID_STRING_LENGTH];
  cass_uuid_string(id, idStr);
  return string(idStr);
}

tuple<string, size_t, FLOAT> TileCodeContainer::_getTileContainer(string uuid)
throw(exception) {
  string stmtStr = ""
    "SELECT * \n"
    "FROM rl.tilecodecontainer\n"
    "WHERE id = " + uuid + ";\n";
  CassStatement* stmt = cass_statement_new(stmtStr.c_str(), 0);

  CassFuture* resultFuture =
    cass_session_execute(db::session, stmt);

  const CassResult* result = cass_future_get_result(resultFuture);

  // If there was an error then the result won't be available.
  if (result == NULL) {
    /* Handle error */
    cass_future_free(resultFuture);
    throw "Query failed.";
  }

  // The future can be freed immediately after getting the result object.
  cass_future_free(resultFuture);

  // This can be used to retrieve on the first row of the result.
  const CassRow* row = cass_result_first_row(result);

  // Now we can retrieve the column values from the row.
  CassUuid id;
  // Get the column value of "id" by name.
  cass_value_get_uuid(cass_row_get_column_by_name(row, "id"), &id);

  cass_int64_t size;
  // Get the column value of "size" by name.
  cass_value_get_int64(cass_row_get_column_by_name(row, "size"), &size);

  cass_double_t initialValue;
  // Get the column value of "initialValue" by name.
  cass_value_get_double(cass_row_get_column_by_name(row, "initialValue"), &initialValue);

  // This will free the result as well as the string pointed to by 'key'.
  cass_result_free(result);

  char idStr[CASS_UUID_STRING_LENGTH];
  cass_uuid_string(id, idStr);
  return make_tuple(string(idStr), size, initialValue);
}

TileCodeContainerCell& TileCodeContainer::at(size_t i) {
  size_t segmentIndex = i / SEGMENT_SIZE;
  size_t innerSegmentIndex = i % SEGMENT_SIZE;

  return _segments[segmentIndex]->at(innerSegmentIndex);
}

}  // namespace coding
}  // namespace rl
