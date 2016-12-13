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

#include <bitset>

#include "rl"
#include "catch.hpp"

using std::bitset;

union Converter { rl::FLOAT f; uint64_t i; };

SCENARIO("floatArrayToBitset converts float array to bit set.",
         "[rl::utility::floatArrayToBitset]") {
  GIVEN("an array of float") {
    rl::floatArray<3> floatArray { 0.1F, 0.2F, 0.3F };

    Converter c1;
    c1.f = floatArray[0];
    bitset<64> bitset_0_1 = c1.i;

    Converter c2;
    c2.f = floatArray[1];
    bitset<64> bitset_0_2 = c2.i;

    Converter c3;
    c3.f = floatArray[2];
    bitset<64> bitset_0_3 = c3.i;

    WHEN("I convert it to bitstring") {
      auto floatArrayBitString = rl::utility::floatArrayToBitset(floatArray);
      THEN("I get the appropriate bitstring") {
        REQUIRE(floatArrayBitString.to_string() ==
                bitset_0_1.to_string() +
                  bitset_0_2.to_string() +
                  bitset_0_3.to_string());
      }
    }
  }
}

SCENARIO("Concatenate two array",
         "[rl::utility::concatArray]") {
  GIVEN("Two array, concatenate them both.") {
    WHEN("I  concatenate them both") {
      auto result = rl::utility::concatArray(
        rl::floatArray<3>{1, 2, 3}, rl::floatArray<2>{4, 5});
      THEN("I get {1, 2, 3, 4, 5} array") {
        REQUIRE(result == rl::floatArray<5>({1, 2, 3, 4, 5}));
      }
    }
  }
}
