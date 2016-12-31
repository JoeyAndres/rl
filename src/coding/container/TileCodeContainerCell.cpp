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

#include <cassandra.h>
#include <string>

#include "db/utility.h"
#include "coding/container/TileCodeContainerCell.h"

using std::string;

namespace rl {
namespace coding {

TileCodeContainerCell::TileCodeContainerCell(
  string tileCodeContainerId, size_t segmentIndex, size_t index) :
  _tileCodeContainerId(tileCodeContainerId),
  _segmentIndex(segmentIndex),
  _index(index) {
}

FLOAT TileCodeContainerCell::get() const {
  const string dataField = "data" + std::to_string(_index);
  string stmtStr = ""
    "SELECT tileCodeContainerId, segmentIndex, " + dataField + "\n"
    "FROM rl.tilecodecontainersegment\n"
    "WHERE tileCodeContainerId = '" + _tileCodeContainerId + "' AND\n"
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

  cass_double_t outVal = 0.0F;
  cass_value_get_double(
    cass_row_get_column_by_name(row, dataField.c_str()), &outVal);

  // Free memory.
  cass_result_free(result);

  return outVal;
}

void TileCodeContainerCell::set(FLOAT val) {
  const string dataField = "data" + std::to_string(_index);
  string stmtStr = ""
    "UPDATE rl.tilecodecontainersegment\n"
    "SET " + dataField + " = " + std::to_string(val) + "\n"
    "WHERE tileCodeContainerId='" + _tileCodeContainerId + "' AND\n"
    "      segmentIndex = " + std::to_string(_segmentIndex) + ";\n";

  CassStatement* stmt = cass_statement_new(stmtStr.c_str(), 0);

  CassFuture* resultFuture =
    cass_session_execute(db::session, stmt);

#ifdef DEBUG
  // Block till the result is back.
  CassError rc = cass_future_error_code(resultFuture);
  const CassResult* result = cass_future_get_result(resultFuture);

  // If there was an error then the result won't be available.
  if (result == NULL) {
    /* Handle error */
    printf("Query result: %s\n", cass_error_desc(rc));
    cass_future_free(resultFuture);
    cass_statement_free(stmt);
    throw "Query failed.";
  }
#endif

  // The future can be freed immediately after getting the result object.
  cass_future_free(resultFuture);
  cass_statement_free(stmt);
}

TileCodeContainerCell& TileCodeContainerCell::operator=(FLOAT val) {
  this->set(val);
  return *this;
}

TileCodeContainerCell& TileCodeContainerCell::operator+=(FLOAT val) {
  this->set(this->get() + val);
  return *this;
}

TileCodeContainerCell::operator FLOAT() const {
  return get();
}

}  // namespace coding
}  // namespace rl

#endif  // #ifdef ENABLE_DB
