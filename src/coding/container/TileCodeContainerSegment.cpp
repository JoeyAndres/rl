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

#ifdef ENABLE_DB

#include "coding/container/TileCodeContainerSegment.h"
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
    cass_statement_new(db::InsertTileCodeContainerSegment.c_str(), 103);

  // Bind the values using the indices of the bind variables.
  cass_statement_bind_string(stmt, 0, _tileCodeContainerId.c_str());
  cass_statement_bind_int64(stmt, 1, _size);
  cass_statement_bind_int64(stmt, 2, _segmentIndex);
  for (size_t i = 0; i < SEGMENT_SIZE; i++) {
    cass_statement_bind_double(stmt, 3 + i, 0.0F);
  }

  CassFuture* queryFuture = cass_session_execute(
    db::session, stmt);

  // Statement objects can be freed immediately after being executed.
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
    "SELECT tileCodeContainerId, size, segmentIndex \n"
    "FROM rl.tilecodecontainersegment\n"
    "WHERE tileCodeContainerId = '" + _tileCodeContainerId + "' AND\n"
    "      segmentIndex = " + std::to_string(_segmentIndex) + ";\n";
  CassStatement* stmt = cass_statement_new(stmtStr.c_str(), 0);

  CassFuture* resultFuture =
    cass_session_execute(db::session, stmt);

  CassError rc = cass_future_error_code(resultFuture);
  const CassResult* result = cass_future_get_result(resultFuture);

  // If there was an error then the result won't be available.
  if (result == NULL) {
    /* Handle error */
    printf("Query result [read]: %s\n", cass_error_desc(rc));
    cass_future_free(resultFuture);
    throw "Query failed.";
  }

  // The future can be freed immediately after getting the result object.
  cass_future_free(resultFuture);
  cass_statement_free(stmt);

  // This can be used to retrieve on the first row of the result.
  const CassRow* row = cass_result_first_row(result);

  cass_int64_t size;
  // Get the column value of "size" by name.
  cass_value_get_int64(cass_row_get_column_by_name(row, "size"), &size);
  _size = size;

  cass_int64_t segmentIndex;
  cass_value_get_int64(
    cass_row_get_column_by_name(row, "segmentIndex"), &segmentIndex);
  _segmentIndex = segmentIndex;

  // This will free the result as well as the string pointed to by 'key'.
  cass_result_free(result);
}

void TileCodeContainerSegment::update() {
}

void TileCodeContainerSegment::delete2() {
  string stmtStr = ""
    "DELETE FROM rl.tilecodecontainersegment\n"
    "WHERE tileCodeContainerId = '" + _tileCodeContainerId + "' AND\n"
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

TileCodeContainerCell TileCodeContainerSegment::operator[](size_t i) const {
  return this->at(i);
}

TileCodeContainerCell TileCodeContainerSegment::at(size_t i) const {
  return TileCodeContainerCell(_tileCodeContainerId, _segmentIndex, i);
}

void TileCodeContainerSegment::createSchema() {
  db::executeStatement(db::TileCodeContainerSegment.c_str());
}

}  // namespace coding
}  // namespace rl

#endif  // #ifdef ENABLE_DB
