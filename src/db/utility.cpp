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

#include <iostream>

#include "db/utility.h"
#include "db/definition.h"

namespace rl {
namespace db {

CassCluster* cluster = nullptr;
CassSession* session = nullptr;
CassFuture* connectFuture = nullptr;

void initialize() {
  if (db::isInitialized()) {
    return;
  }

  // Setup and connect to cluster.
  rl::db::cluster = cass_cluster_new();
  rl::db::session = cass_session_new();

  // Add contact points.
  cass_cluster_set_contact_points(db::cluster, "127.0.0.1");

  // Provide the cluster object as configuration to connect the session.
  db::connectFuture = cass_session_connect(
    db::session, db::cluster);

  // This operation will block until the result is ready.
  CassError rc = cass_future_error_code(rl::db::connectFuture);

#ifdef DEBUG
  std::cout << "TileCodeContainer::initialize" << std::endl;

  if (rc != CASS_OK) {
    rl::db::terminate();

    auto errorStr = cass_error_desc(rc);
    std::cerr << "Connect result: " << errorStr << std::endl;
  }
#endif

  // Create key schemas.
  db::createKeySpace();
}

void terminate() {
#ifdef DEBUG
  std::cout << "TileCodeContainer::terminate" << std::endl;
#endif

  // Don't do a thing if already terminated.
  if (!isInitialized()) {
    return;
  }

  cass_future_wait(db::connectFuture);
  cass_future_free(db::connectFuture);
  db::connectFuture = nullptr;
  cass_session_free(db::session);
  db::session = nullptr;
  cass_cluster_free(db::cluster);
  db::cluster = nullptr;
}

bool isInitialized() {
  return db::connectFuture != nullptr &&
    db::session != nullptr &&
    db::cluster != nullptr;
}

void executeStatement(const string& stmtStr) {
  CassStatement* stmt = cass_statement_new(stmtStr.c_str(), 0);

  CassFuture* resultFuture =
    cass_session_execute(db::session, stmt);

  if (cass_future_error_code(resultFuture) == CASS_OK) {

  } else {
    // Deal With Error.
    /* Handle error */
    const char* message;
    size_t message_length;
    cass_future_error_message(resultFuture, &message, &message_length);
    std::cerr << message << std::endl;
  }

  cass_statement_free(stmt);
  cass_future_free(resultFuture);
}

void createKeySpace() {
  db::executeStatement(db::RLKeySpace.c_str());
}

CassUuid genUuid() {
  CassUuidGen* uuidGen = cass_uuid_gen_new();
  CassUuid id;
  cass_uuid_gen_from_time(uuidGen, 1234, &id);
  cass_uuid_gen_free(uuidGen);
  return id;
}

}  // namespace db
}  // namespace rl
