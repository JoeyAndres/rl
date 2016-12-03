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

SCENARIO("StateActionTransition have the ability to represent offline model "
           "for offline caclulation",
         "[StateActionTransition]") {
  GIVEN("StateActionTransition instance") {
    rl::agent::StateActionTransition<rl::INT> sat(1.0F, 0.2F);
    WHEN("Size is acquired") {
      THEN("Returns 0") {
        REQUIRE(sat.getSize() == 0);
      }
    }

    GIVEN("A set of states") {
      rl::spState<rl::INT> state01(new rl::INT(1));
      rl::spState<rl::INT> state02(new rl::INT(2));
      rl::spState<rl::INT> state03(new rl::INT(3));
      WHEN("Update all of them. One more than the other.") {
        sat.update(state01, 10);
        REQUIRE(sat.getSize() == 1);
        REQUIRE(sat.getNextState() == state01);  // 1 states stored.

        sat.update(state02, 10);
        sat.update(state02, 10);
        REQUIRE(sat.getSize() == 2);  // 2 states stored.

        sat.update(state03, 10);
        sat.update(state03, 10);
        sat.update(state03, 10);
        REQUIRE(sat.getSize() == 3);  // 3 states stored.

        THEN("The one exposed to most reward and often will likely be chosen "
               "more") {
          rl::UINT state01OccurenceCount = 0,
            state02OccurenceCount = 0,
            state03OccurenceCount = 0;

          for (rl::UINT i = 0; i < 1000; i++) {
            rl::spState<rl::INT> state = sat.getNextState();
            if (state == state01) {
              state01OccurenceCount++;
            } else if (state == state02) {
              state02OccurenceCount++;
            } else if (state == state03) {
              state03OccurenceCount++;
            } else {
              REQUIRE(false /* Not supposed to happen. */);
            }
          }

          REQUIRE(state01OccurenceCount < state02OccurenceCount);
          REQUIRE(state02OccurenceCount < state03OccurenceCount);
        }
      }
    }
  }

  GIVEN("empty StateActionTransition (No states)") {
    StateActionTransition<rl::INT> sat(1.0F, 0.2F);
    WHEN("I try to access the reward") {
      THEN("I get an exception.") {
        StateActionTransition<rl::INT> sat(1.0F, 0.2F);

        bool exceptionCalled = false;
        try {
          sat.getReward(rl::spState<rl::INT>(new rl::INT(23)));
        } catch (rl::agent::StateActionTransitionException& exception) {
          exceptionCalled = true;
        }
        REQUIRE(exceptionCalled);
      }
    }

    WHEN("I try to access next state") {
      THEN("I get an exception.") {
        bool exceptionCalled = false;
        try {
          sat.getNextState();
        } catch (rl::agent::StateActionTransitionException& exception) {
          exceptionCalled = true;
        }
        REQUIRE(exceptionCalled);
      }
    }

    WHEN("I try to access a reward for a state that was not know to this "
           "StateActionTransition") {
      rl::spState<rl::INT> state10(new rl::INT(10));
      rl::spState<rl::INT> state23(new rl::INT(23));
      sat.update(state10, 100);
      THEN("I get an exception.") {
        bool exceptionCalled = false;
        try {
          sat.getReward(state23);
        } catch (rl::agent::StateActionTransitionException& exception) {
          exceptionCalled = true;
        }
        REQUIRE(exceptionCalled);
      }
    }
  }
}
