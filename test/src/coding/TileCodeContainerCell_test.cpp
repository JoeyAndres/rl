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

#include <chrono>
#include <thread>

#include "rl"
#include "catch.hpp"

namespace rl {
namespace coding {

SCENARIO("TileCodeContainerCell, a single weight in TileCodeContainer.",
         "[TileCodeContainerCell]") {
  GIVEN("A default TileCodeContainerSegment instance") {
    rl::coding::TileCodeContainer tcc(1000, 0.0F);

    WHEN("TileCodeContainerCell is initialized with index 0, 23, 50, 99") {
      TileCodeContainerCell tccc1(tcc.getID(), 0, 0);
      TileCodeContainerCell tccc2(tcc.getID(), 0, 23);
      TileCodeContainerCell tccc3(tcc.getID(), 0, 50);
      TileCodeContainerCell tccc4(tcc.getID(), 0, 99);

      THEN("All have 0 values") {
        REQUIRE(tccc1 == 0.0F);
        REQUIRE(tccc2 == 0.0F);
        REQUIRE(tccc3 == 0.0F);
        REQUIRE(tccc4 == 0.0F);
      }
    }

    tcc.delete2();
  }

  GIVEN("A TileCodeContainerCell instance") {
    rl::coding::TileCodeContainer tcc(1000, 0.0F);

    WHEN("I change the value of index 0 from 0.0 to 69.0") {
      TileCodeContainerCell tccc(tcc.getID(), 0, 0);
      tccc = 69.0F;

      THEN("That index 0 cell is now 69.0") {
        REQUIRE(tccc == 69.0F);
      }
    }

    WHEN("I change the value of index 99 from 0.0 to -37.0") {
      TileCodeContainerCell tccc(tcc.getID(), 0, 99);
      tccc = -37.0F;

      THEN("That index 0 cell is now 69.0") {
        REQUIRE(tccc == -37.0F);
      }
    }

    tcc.delete2();
  }
}

}  // namespace coding
}  // namespace rl
