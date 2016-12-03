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

#include <vector>

#include "rl"
#include "catch.hpp"

SCENARIO("TileCodeUNH retrieves the correct feature vector",
         "[TileCodeUNH]") {
  GIVEN("TileCodeUNH instance") {
    vector<rl::coding::DimensionInfo<rl::FLOAT> > dimensionalInfoVector = {
      rl::coding::DimensionInfo<rl::FLOAT>(-0.5F, 0.5F, 3, 0),
      rl::coding::DimensionInfo<rl::FLOAT>(-0.5F, 0.5F, 3, 0)
    };

    rl::coding::TileCodeUNH tileCode(dimensionalInfoVector, 4, 100);

    WHEN("TileCodeUNH::getDimension is called.") {
      THEN("Returns 3") {
        REQUIRE(tileCode.getDimension() == 2);
      }
    }

    WHEN("TileCodeUNH::getSize is called.") {
      THEN("Returns 100") {
        REQUIRE(tileCode.getSize() == 100);
      }
    }

    // The rest are hash in which I don't want to predict. They are all tested
    // by TileCode_test.cpp anyway.
  }
}
