//
// Created by jandres on 12/11/16.
//

#include <set>

#include "rl"

#include "../../lib/catch.hpp"

using namespace std;

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

    WHEN ("Adding a state-action.") {
      container.addStateAction(rl::agent::StateAction<int, int>(state0, action1), 1);
      THEN ("Size should be 1p") {
        REQUIRE(container.getMap().size() == 1);
      }
    }
  }

  GIVEN("Empty rl::agent::StateActionPairContainer") {
    rl::agent::StateActionPairContainer<int, int> container;

    WHEN ("Calling addSate with 5 actions.") {
      container.addState(state0, -1, rl::spActionSet<int>(
      {
        action1, action2, action3, action4, action5
      }
      ));
      THEN ("Changes the count to 5.") {
        REQUIRE(container.getMap().size() == 5);
      }
    }
  }

  GIVEN("Empty rl::agent::StateActionPairContainer") {
    rl::agent::StateActionPairContainer<int, int> container;

    WHEN ("Calling addAction with 5 states.") {
      container.addAction(action5, -1, rl::spStateSet<int>(
        {
          state0, state1, state2, state3, state4
        }
      ));
      THEN ("Changes the count to 5.") {
        REQUIRE(container.getMap().size() == 5);
      }
    }
  }

  GIVEN("A non-empty rl::agent::StateActionPairContainer") {
    rl::agent::StateActionPairContainer<int, int> container;
    container.addStateAction(rl::agent::StateAction<int, int>(state0, action1), 1);

    WHEN ("Calling setStateActionValue.") {
      REQUIRE(container.getStateActionValue(rl::agent::StateAction<int, int>(state0, action1)) == 1);
      container.setStateActionValue(rl::agent::StateAction<int, int>(state0, action1), 2);
      THEN ("Changes the value of an existing state action.") {
        REQUIRE(container.getStateActionValue(rl::agent::StateAction<int, int>(state0, action1)) == 2);
      }
    }
  }
}
