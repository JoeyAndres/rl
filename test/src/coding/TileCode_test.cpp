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

SCENARIO("Tile code retrieves the correct feature vector",
         "[TileCodeCorrect]") {
  GIVEN("TileCodeCorrect instance") {
    array<rl::coding::DimensionInfo<rl::FLOAT>, 2> dimensionalInfoVector = {
      rl::coding::DimensionInfo<rl::FLOAT>(-0.5F, 0.5F, 3, 0),
      rl::coding::DimensionInfo<rl::FLOAT>(-0.5F, 0.5F, 3, 0)
    };

    rl::coding::TileCodeCorrect<2, 4> tileCode(dimensionalInfoVector);

    WHEN("TileCode::getDimension is called.") {
      THEN("Returns 2") {
        REQUIRE(tileCode.getDimension() == 2);
      }
    }

    WHEN("TileCode::getSize is called.") {
      THEN("Returns (3+1)*(3*1)*4 = 16*4") {
        REQUIRE(tileCode.getSize() == 16*4);
      }
    }

    WHEN("TileCode::paramToGridValue is called for -0.4.") {
      THEN("Return 0") {
        REQUIRE(tileCode.paramToGridValue(-0.4, 1, 1) == 0);
      }
    }

    WHEN("TileCode::getFeatureVector is called for (-0.4, -0.4).") {
      THEN("Return (0, 16, 32, 48)") {
        auto fv = tileCode.getFeatureVector(rl::floatArray<2>({-0.4, -0.4}));
        decltype(fv) result { 0, 16, 32, 48 };
        REQUIRE(fv == result);
      }
    }
  }
}
