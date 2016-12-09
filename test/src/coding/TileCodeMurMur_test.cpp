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

#include <array>

#include "rl"
#include "catch.hpp"

using std::array;

SCENARIO("TileCodeMurMur retrieves the correct feature vector",
         "[TileCodeMurMur]") {
  GIVEN("TileCodeMurMur instance") {
    array<rl::coding::DimensionInfo<rl::FLOAT>, 2> dimensionalInfoVector = {
      rl::coding::DimensionInfo<rl::FLOAT>(-0.5F, 0.5F, 3, 0),
      rl::coding::DimensionInfo<rl::FLOAT>(-0.5F, 0.5F, 3, 0)
    };

    rl::coding::TileCodeMurMur<2, 4> tileCode(dimensionalInfoVector, 100);

    WHEN("TileCodeMurMur::getDimension is called.") {
      THEN("Returns 3") {
        REQUIRE(tileCode.getDimension() == 2);
      }
    }

    WHEN("TileCodeMurMur::getSize is called.") {
      THEN("Returns 100") {
        REQUIRE(tileCode.getSize() == 100);
      }
    }

    // The rest are hash in which I don't want to predict. They are all tested
    // by TileCode_test.cpp anyway.
  }
}
