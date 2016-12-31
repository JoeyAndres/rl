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

#include <cassandra.h>
#include <string>

using std::string;

namespace rl {
namespace db {

extern CassCluster* cluster;
extern CassSession* session;
extern CassFuture* connectFuture;

bool isInitialized();

/**
   * Initialize connections and schema (if it doesn't exist yet).
   */
void initialize();

/**
 * Terminate connections.
 */
void terminate();

void executeStatement(const string& stmtStr);

/**
 * Creates the keyspace to be used by this app.
 */
void createKeySpace();

CassUuid genUuid();

}  // namespace db
}  // namespace rl
