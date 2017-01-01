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

  "  data0 double,\n"
  "  data1 double,\n"
  "  data2 double,\n"
  "  data3 double,\n"
  "  data4 double,\n"
  "  data5 double,\n"
  "  data6 double,\n"
  "  data7 double,\n"
  "  data8 double,\n"
  "  data9 double,\n"
  "  data10 double,\n"
  "  data11 double,\n"
  "  data12 double,\n"
  "  data13 double,\n"
  "  data14 double,\n"
  "  data15 double,\n"
  "  data16 double,\n"
  "  data17 double,\n"
  "  data18 double,\n"
  "  data19 double,\n"
  "  data20 double,\n"
  "  data21 double,\n"
  "  data22 double,\n"
  "  data23 double,\n"
  "  data24 double,\n"
  "  data25 double,\n"
  "  data26 double,\n"
  "  data27 double,\n"
  "  data28 double,\n"
  "  data29 double,\n"
  "  data30 double,\n"
  "  data31 double,\n"
  "  data32 double,\n"
  "  data33 double,\n"
  "  data34 double,\n"
  "  data35 double,\n"
  "  data36 double,\n"
  "  data37 double,\n"
  "  data38 double,\n"
  "  data39 double,\n"
  "  data40 double,\n"
  "  data41 double,\n"
  "  data42 double,\n"
  "  data43 double,\n"
  "  data44 double,\n"
  "  data45 double,\n"
  "  data46 double,\n"
  "  data47 double,\n"
  "  data48 double,\n"
  "  data49 double,\n"
  "  data50 double,\n"
  "  data51 double,\n"
  "  data52 double,\n"
  "  data53 double,\n"
  "  data54 double,\n"
  "  data55 double,\n"
  "  data56 double,\n"
  "  data57 double,\n"
  "  data58 double,\n"
  "  data59 double,\n"
  "  data60 double,\n"
  "  data61 double,\n"
  "  data62 double,\n"
  "  data63 double,\n"
  "  data64 double,\n"
  "  data65 double,\n"
  "  data66 double,\n"
  "  data67 double,\n"
  "  data68 double,\n"
  "  data69 double,\n"
  "  data70 double,\n"
  "  data71 double,\n"
  "  data72 double,\n"
  "  data73 double,\n"
  "  data74 double,\n"
  "  data75 double,\n"
  "  data76 double,\n"
  "  data77 double,\n"
  "  data78 double,\n"
  "  data79 double,\n"
  "  data80 double,\n"
  "  data81 double,\n"
  "  data82 double,\n"
  "  data83 double,\n"
  "  data84 double,\n"
  "  data85 double,\n"
  "  data86 double,\n"
  "  data87 double,\n"
  "  data88 double,\n"
  "  data89 double,\n"
  "  data90 double,\n"
  "  data91 double,\n"
  "  data92 double,\n"
  "  data93 double,\n"
  "  data94 double,\n"
  "  data95 double,\n"
  "  data96 double,\n"
  "  data97 double,\n"
  "  data98 double,\n"
  "  data99 double,\n"

  "  PRIMARY KEY (tileCodeContainerId, segmentIndex)"
  ");";

}  // namespace db
}  // namespace rl

