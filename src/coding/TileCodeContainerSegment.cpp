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

#include "coding/TileCodeContainerSegment.h"
#include "db/definition.h"
#include "db/manipulation.h"
#include "db/utility.h"

namespace rl {
namespace coding {

TileCodeContainerSegment::TileCodeContainerSegment(
  const string& tileCodeContainerId,
  size_t size,
  size_t index) :
  _tileCodeContainerId(tileCodeContainerId),
  _size(size),
  _segmentIndex(index) {
  _data = vector<FLOAT>(_size, 0);
  // TODO: One place to set this up.
  _data2 = vector<TileCodeContainerCell>(
    _size,
    TileCodeContainerCell(_tileCodeContainerId, index, 0));
  for (size_t i = 0; i < _data2.size(); i++) {
    _data2[i].setIndex(i);
  }
  db::initialize();
  TileCodeContainerSegment::createSchema();
  create();
}

TileCodeContainerSegment::TileCodeContainerSegment(
  const string& tileCodeContainerId, size_t index) :
  _tileCodeContainerId(tileCodeContainerId),
  _segmentIndex(index) {
  db::initialize();
  TileCodeContainerSegment::createSchema();
  read();
}

void TileCodeContainerSegment::create() {
  CassStatement* stmt =
    cass_statement_new(db::InsertTileCodeContainerSegment.c_str(), 4);

  CassUuid tileCodeContainerId;
  cass_uuid_from_string(_tileCodeContainerId.c_str(), &tileCodeContainerId);

  CassCollection* list = cass_collection_new(CASS_COLLECTION_TYPE_LIST, _size);
  for (size_t i = 0; i < _size; i++) {
    cass_collection_append_double(list, 0.0F);
  }

  // Bind the values using the indices of the bind variables.
  cass_statement_bind_uuid(stmt, 0, tileCodeContainerId);
  cass_statement_bind_int64(stmt, 1, _size);
  cass_statement_bind_int64(stmt, 2, _segmentIndex);
  cass_statement_bind_collection(stmt, 3, list);

  CassFuture* queryFuture = cass_session_execute(
    db::session, stmt);

  // Statement objects can be freed immediately after being executed.
  cass_collection_free(list);
  cass_statement_free(stmt);

  // This will block until the query has finished.
  CassError rc = cass_future_error_code(queryFuture);

  if (rc != CASS_OK) {
    printf("Query result: %s\n", cass_error_desc(rc));
    cass_future_free(queryFuture);
    // TODO(jandres): Exception for failed queries.
    throw "Query failed.";
  }

  cass_future_free(queryFuture);
}

void TileCodeContainerSegment::read() {
  string stmtStr = ""
    "SELECT * \n"
    "FROM rl.tilecodecontainersegment\n"
    "WHERE tileCodeContainerId = " + _tileCodeContainerId + " AND\n"
    "      segmentIndex = " + std::to_string(_segmentIndex) + ";\n";
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
  cass_statement_free(stmt);

  // This can be used to retrieve on the first row of the result.
  const CassRow* row = cass_result_first_row(result);

  // Now we can retrieve the column values from the row.
  CassUuid id;
  // Get the column value of "id" by name.
  cass_value_get_uuid(cass_row_get_column_by_name(row, "id"), &id);

  CassUuid tileCodeContainerId;
  cass_value_get_uuid(
    cass_row_get_column_by_name(row, "tileCodeContainerId"),
    &tileCodeContainerId);
  char tileCodeContainerIdStr[CASS_UUID_STRING_LENGTH];
  cass_uuid_string(tileCodeContainerId, tileCodeContainerIdStr);
  _tileCodeContainerId = tileCodeContainerIdStr;

  cass_int64_t size;
  // Get the column value of "size" by name.
  cass_value_get_int64(cass_row_get_column_by_name(row, "size"), &size);
  _size = size;

  cass_int64_t segmentIndex;
  cass_value_get_int64(
    cass_row_get_column_by_name(row, "segmentIndex"), &segmentIndex);
  _segmentIndex = segmentIndex;

  _data = vector<FLOAT>(_size, 0.0F);
  _data2 = vector<TileCodeContainerCell>(
    _size,
    TileCodeContainerCell(_tileCodeContainerId, _segmentIndex, 0));
  for (size_t i = 0; i < _data2.size(); i++) {
    _data2[i].setIndex(i);
  }

  const CassValue* data = cass_row_get_column_by_name(row, "data");
  CassIterator* iterator = cass_iterator_from_collection(data);
  size_t i = 0;
  while (cass_iterator_next(iterator)) {
    const CassValue* value = cass_iterator_get_value(iterator);
    double outVal = 0.0F;
    cass_value_get_double(value, &outVal);
    _data[i++] = outVal;
  }

  // This will free the result as well as the string pointed to by 'key'.
  cass_iterator_free(iterator);
  cass_result_free(result);
}

void TileCodeContainerSegment::update() {

}

void TileCodeContainerSegment::delete2() {
  string stmtStr = ""
    "DELETE FROM rl.tilecodecontainersegment\n"
    "WHERE tileCodeContainerId = " + _tileCodeContainerId + " AND\n"
    "      segmentIndex = " + std::to_string(_segmentIndex) + ";\n";
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

  cass_statement_free(stmt);
  cass_future_free(resultFuture);
}

TileCodeContainerCell& TileCodeContainerSegment::at(size_t i) {
  return _data2[i];
}

TileCodeContainerCell TileCodeContainerSegment::at(size_t i) const {
  return _data2[i];
}

void TileCodeContainerSegment::createSchema() {
  db::executeStatement(db::TileCodeContainerSegment.c_str());
}

}  // namespace coding
}  // namespace rl
