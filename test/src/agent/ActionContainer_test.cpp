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

SCENARIO("Agent have a storage for actions.",
         "[rl::agent::ActionContainer]") {
  GIVEN("ActionContainer instance from no-arg constructor.") {
    rl::agent::ActionContainer<rl::INT> asNoArg;

    WHEN("I first access action.") {
      auto actions = asNoArg.getActionSet();
      THEN("It is empty.") {
        REQUIRE(actions.size() == 0);
      }
    }
  }

  GIVEN("ActionContainer instance with some actions initialize.") {
    rl::spAction<rl::INT> action1(new rl::INT(1));
    rl::spAction<rl::INT> action2(new rl::INT(2));
    rl::spAction<rl::INT> action3(new rl::INT(3));
    rl::spAction<rl::INT> action4(new rl::INT(4));

    rl::agent::ActionContainer<rl::INT> as(rl::spActionSet<rl::INT>({
                                                                action1,
                                                                action2,
                                                                action3,
                                                                action4 }));

    WHEN("I first access action.") {
      auto actions = as.getActionSet();
      THEN("It should return 4") {
        REQUIRE(actions.size() == 4);
      }
    }
  }
}
