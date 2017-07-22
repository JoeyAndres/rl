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

SCENARIO("StateActionPairContainer a storage for state-action pair.",
         "[rl::agent::StateActionPairContainer]") {
  rl::spState<int> state0(new int(0));
  rl::spState<int> state1(new int(1));
  rl::spState<int> state2(new int(2));
  rl::spState<int> state3(new int(3));
  rl::spState<int> state4(new int(4));

  rl::spAction<int> action1(new int(1));
  rl::spAction<int> action2(new int(2));
  rl::spAction<int> action3(new int(3));
  rl::spAction<int> action4(new int(4));
  rl::spAction<int> action5(new int(5));

  GIVEN("Empty rl::agent::StateActionPairContainer instance") {
    rl::agent::StateActionPairContainer<int, int> container;

    WHEN("Adding a state-action.") {
      container.addStateAction(rl::agent::StateAction<int, int>(state0,
                                                                action1), 1);
      THEN("Size should be 1p") {
        REQUIRE(container.size() == 1);
      }
    }
  }

  GIVEN("Empty rl::agent::StateActionPairContainer") {
    rl::agent::StateActionPairContainer<int, int> container;

    WHEN("Calling addSate with 5 actions.") {
      container.addState(state0, -1, rl::spActionSet<int>(
      {
        action1, action2, action3, action4, action5
      }));
      THEN("Changes the count to 5.") {
        REQUIRE(container.size() == 5);
      }
    }
  }

  GIVEN("Empty rl::agent::StateActionPairContainer") {
    rl::agent::StateActionPairContainer<int, int> container;

    WHEN("Calling addAction with 5 states.") {
      container.addAction(action5, -1, rl::spStateSet<int>(
        {
          state0, state1, state2, state3, state4
        }));
      THEN("Changes the count to 5.") {
        REQUIRE(container.size() == 5);
      }
    }
  }

  GIVEN("A non-empty rl::agent::StateActionPairContainer") {
    rl::agent::StateActionPairContainer<int, int> container;
    container.addStateAction(rl::agent::StateAction<int, int>(state0,
                                                              action1), 1);

    WHEN("Calling setStateActionValue.") {
      REQUIRE(container.getStateActionValue(
        rl::agent::StateAction<int, int>(state0, action1)) == 1);
      container.setStateActionValue(
        rl::agent::StateAction<int, int>(state0, action1), 2);
      THEN("Changes the value of an existing state action.") {
        REQUIRE(container.getStateActionValue(
          rl::agent::StateAction<int, int>(state0, action1)) == 2);
      }
    }
  }
}
