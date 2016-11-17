/**
 * StateActionTransition_test.cpp
 */

#include <vector>
#include <iostream>

#include "rl"

#include "../../lib/catch.hpp"

using std::vector;

using namespace rl;
using namespace rl::algorithm;
using namespace std;

SCENARIO("StateActionTransition have the ability to represent offline model for offline caclulation",
         "[StateActionTransition]") {
  GIVEN("StateActionTransition instance") {
    StateActionTransition<rl::INT> sat(1.0F, 0.2F);
    WHEN("Size is acquired") {
      THEN ("Returns 0") {
        REQUIRE(sat.getSize() == 0);
      }
    }
    
    GIVEN("A set of states") {
      rl::INT state01(1);
      rl::INT state02(2);
      rl::INT state03(3);
      WHEN("Update all of them. One more than the other.") {
        sat.update(state01, 10);
        REQUIRE(sat.getSize() == 1);
        REQUIRE(sat.getNextState() == state01);  // 1 states stored.

        rl::INT state02(2);
        sat.update(state02, 10);
        sat.update(state02, 10);
        REQUIRE(sat.getSize() == 2);  // 2 states stored.

        rl::INT state03(3);
        sat.update(state03, 10);
        sat.update(state03, 10);
        sat.update(state03, 10);
        REQUIRE(sat.getSize() == 3);  // 3 states stored.

        THEN ("The one exposed to most reward and often will likely be chosen more") {
          rl::UINT state01OccurenceCount = 0,
            state02OccurenceCount = 0,
            state03OccurenceCount = 0;

          for (rl::UINT i = 0; i < 1000; i++) {
            const rl::INT& state = sat.getNextState();
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
      THEN ("I get an exception.") {
        StateActionTransition<rl::INT> sat(1.0F, 0.2F);

        bool exceptionCalled = false;
        try {
          sat.getReward(rl::INT(23));
        } catch (StateActionTransitionException& exception) {
          //cout << exception.what() << endl;
          exceptionCalled = true;
        }
        REQUIRE(exceptionCalled);
      }
    }

    WHEN("I try to access next state") {
      THEN ("I get an exception.") {
        bool exceptionCalled = false;
        try {
          sat.getNextState();
        } catch (StateActionTransitionException& exception) {
          //cout << exception.what() << endl;
          exceptionCalled = true;
        }
        REQUIRE(exceptionCalled);
      }
    }

    WHEN("I try to access a reward for a state that was not know to this StateActionTransition") {
      sat.update(10, 100);
      THEN ("I get an exception.") {
        bool exceptionCalled = false;
        try {
          sat.getReward(23);
        } catch (StateActionTransitionException& exception) {
          //cout << exception.what() << endl;
          exceptionCalled = true;
        }
        REQUIRE(exceptionCalled);
      }
    }
  }
}