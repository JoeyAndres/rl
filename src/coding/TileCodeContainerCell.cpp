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
#include <string>

#include "db/utility.h"
#include "coding/TileCodeContainerCell.h"

using std::string;

namespace rl {
namespace coding {

TileCodeContainerCell::TileCodeContainerCell(
  string tileCodeContainerId, size_t segmentIndex, size_t index) :
  _tileCodeContainerId(tileCodeContainerId),
  _segmentIndex(segmentIndex),
  _index(index) {
}

void TileCodeContainerCell::setIndex(size_t index) {
  _index = index;
}

FLOAT TileCodeContainerCell::get() const {
  string stmtStr = ""
    "SELECT *\n"
    "FROM rl.tilecodecontainersegment\n"
    "WHERE tileCodeContainerId = " + _tileCodeContainerId + " AND\n"
    "      segmentIndex = " + std::to_string(_segmentIndex) + ";\n";

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

  // The future can be freed immediately after getting the result object.
  cass_future_free(resultFuture);
  cass_statement_free(stmt);

  // This can be used to retrieve on the first row of the result.
  const CassRow* row = cass_result_first_row(result);

  const CassValue* data = cass_row_get_column_by_name(row, "data");
  CassIterator* iterator = cass_iterator_from_collection(data);
  // cassandra have 1-based indexing instead of 0-based when
  // retrieving.
  for (size_t i = 1; i <= _index + 1; i++) {
    cass_iterator_next(iterator);  // Advance the iterator.
  }

  const CassValue* value = cass_iterator_get_value(iterator);
  cass_double_t outVal = 0.0F;
  cass_value_get_double(value, &outVal);

  // Free memory.
  cass_iterator_free(iterator);
  cass_result_free(result);

  return outVal;
}

void TileCodeContainerCell::set(FLOAT val) {
  string stmtStr = ""
    "UPDATE rl.tilecodecontainersegment\n"
    "SET data[" + std::to_string(_index) + "] = " + std::to_string(val) + "\n"
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
}

TileCodeContainerCell& TileCodeContainerCell::operator=(FLOAT val) {
  this->set(val);
  return *this;
}

TileCodeContainerCell::operator FLOAT() const {
  return get();
}

}  // namespace coding
}  // namespace rl
