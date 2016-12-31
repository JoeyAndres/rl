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

#include "db/definition.h"

namespace rl {
namespace db {

string RLKeySpace = ""
  "CREATE KEYSPACE IF NOT EXISTS rl\n"
  "  WITH replication = {'class': 'SimpleStrategy', 'replication_factor' : 3};";

string TileCodeContainer = ""
  "CREATE TABLE IF NOT EXISTS rl.tilecodecontainer (\n"
  "  id uuid PRIMARY KEY,\n"
  "  size bigint,\n"
  "  initialValue double\n"
  ");";

string TileCodeContainerSegment = ""
  "CREATE TABLE IF NOT EXISTS rl.tilecodecontainersegment (\n"
  "  tileCodeContainerId uuid,\n"
  "  size bigint,\n"
  "  segmentIndex bigint,\n"
  "  data list<double>,\n"
  "  PRIMARY KEY (tileCodeContainerId, segmentIndex)"
  ");";

}  // namespace db
}  // namespace rl

