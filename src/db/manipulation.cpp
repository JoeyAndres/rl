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

#include "db/manipulation.h"

namespace rl {
namespace db {

string InsertTileCodeContainer = ""
  "INSERT INTO rl.tilecodecontainer ("
  "id, size, initialValue) VALUES (?, ?, ?);";

string InsertTileCodeContainerSegment = ""
  "INSERT INTO rl.tilecodecontainersegment ("
  "tileCodeContainerId, "
  "size,\n"
  "segmentIndex,\n"

  "data0,\n"
  "data1,\n"
  "data2,\n"
  "data3,\n"
  "data4,\n"
  "data5,\n"
  "data6,\n"
  "data7,\n"
  "data8,\n"
  "data9,\n"
  "data10,\n"
  "data11,\n"
  "data12,\n"
  "data13,\n"
  "data14,\n"
  "data15,\n"
  "data16,\n"
  "data17,\n"
  "data18,\n"
  "data19,\n"
  "data20,\n"
  "data21,\n"
  "data22,\n"
  "data23,\n"
  "data24,\n"
  "data25,\n"
  "data26,\n"
  "data27,\n"
  "data28,\n"
  "data29,\n"
  "data30,\n"
  "data31,\n"
  "data32,\n"
  "data33,\n"
  "data34,\n"
  "data35,\n"
  "data36,\n"
  "data37,\n"
  "data38,\n"
  "data39,\n"
  "data40,\n"
  "data41,\n"
  "data42,\n"
  "data43,\n"
  "data44,\n"
  "data45,\n"
  "data46,\n"
  "data47,\n"
  "data48,\n"
  "data49,\n"
  "data50,\n"
  "data51,\n"
  "data52,\n"
  "data53,\n"
  "data54,\n"
  "data55,\n"
  "data56,\n"
  "data57,\n"
  "data58,\n"
  "data59,\n"
  "data60,\n"
  "data61,\n"
  "data62,\n"
  "data63,\n"
  "data64,\n"
  "data65,\n"
  "data66,\n"
  "data67,\n"
  "data68,\n"
  "data69,\n"
  "data70,\n"
  "data71,\n"
  "data72,\n"
  "data73,\n"
  "data74,\n"
  "data75,\n"
  "data76,\n"
  "data77,\n"
  "data78,\n"
  "data79,\n"
  "data80,\n"
  "data81,\n"
  "data82,\n"
  "data83,\n"
  "data84,\n"
  "data85,\n"
  "data86,\n"
  "data87,\n"
  "data88,\n"
  "data89,\n"
  "data90,\n"
  "data91,\n"
  "data92,\n"
  "data93,\n"
  "data94,\n"
  "data95,\n"
  "data96,\n"
  "data97,\n"
  "data98,\n"
  "data99 \n"

  ") VALUES (?, ?, ?, "
  "?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
  "?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
  "?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
  "?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
  "?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
  "?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
  "?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
  "?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
  "?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
  "?, ?, ?, ?, ?, ?, ?, ?, ?, ?"
  ");";

}  // db
}  // rl
