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

#include "catch.hpp"

#include "rl"
#include "RandomWalkEnvironment.h"

SCENARIO("rl::agent::StateActionPairValueComparison can compare "
           "two state action pair.",
         "[rl::agent::StateActionPairValueComparison]") {
  GIVEN("rl::agent::StateActionPairValueComparison") {
    auto B = rl::spState<int>(new int(RandomWalkEnvironment::State::B));
    auto L = rl::spAction<int>(new int(RandomWalkEnvironment::Action::L));

    auto A = rl::spState<int>(new int(RandomWalkEnvironment::State::A));

    rl::agent::StateActionPairValueComparison<int, int> sapvc;
    auto sav1 = std::pair<rl::agent::StateAction<int, int>, double>(
      rl::agent::StateAction<int, int>(B, L), 1.0F);
    auto sav2 = std::pair<rl::agent::StateAction<int, int>, double>(
      rl::agent::StateAction<int, int>(A, L), 2.0F);

    WHEN("I compare sa1 and sa2 using "
           "rl::agent::StateActionPairValueComparison.") {
      THEN("It should return sa1 > sa2.") {
        REQUIRE(sapvc(sav2, sav1));
      }
    }
  }
}
