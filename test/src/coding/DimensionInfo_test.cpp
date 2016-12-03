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

SCENARIO("DimensionalInfo represents a dimension in TileCode",
         "[DimensionalInfo]") {
  GIVEN("DimensionalInfo instance") {
    rl::coding::DimensionInfo<rl::FLOAT> dim(-0.5F, 0.5F, 3, 0);


    WHEN("DimensionalInfo::GetOffsets") {
      THEN("Returns 1/3") {
        REQUIRE((dim.GetOffsets() - 1.0f/3.0f) < 0.001f);
      }
    }

    WHEN("DimensionalInfo::GetGridCountReal") {
      THEN("Returns 4") {
        REQUIRE(dim.GetGridCountReal() == 4);
      }
    }

    WHEN("DimensionalInfo::GetGridCountIdeal") {
      THEN("Returns 3") {
        REQUIRE(dim.GetGridCountIdeal() == 3);
      }
    }

    WHEN("DimensionalInfo::GetRangeDifference") {
      THEN("Returns 1") {
        REQUIRE((dim.GetRangeDifference() - 1.0f) < 0.001f);
      }
    }

    WHEN("DimensionalInfo::getGeneralizationScale") {
      THEN("Returns 0") {
        REQUIRE((dim.getGeneralizationScale() - 0.0f) < 0.001f);
      }
    }
  }
}
