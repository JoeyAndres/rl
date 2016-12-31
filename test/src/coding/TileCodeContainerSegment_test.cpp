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

#include "rl"
#include "catch.hpp"

SCENARIO("TileCodeContainerSegment saves segment of the weight vector",
         "[TileCodeContainerSegment]") {
  GIVEN("TileCodeContainerSegment instance") {
    rl::coding::TileCodeContainer tcc(1000, 0.0F);
    rl::coding::TileCodeContainerSegment tccs(tcc.getID(), 0);
    WHEN("Initialized") {
      THEN("An element exist") {
        REQUIRE(tccs.at(0) == 0.0F);
      }
    }

    tcc.delete2();
  }
}
