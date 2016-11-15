//
// Created by jandres on 12/11/16.
//

#include <set>

#include "rl"

#include "../../lib/catch.hpp"

using namespace std;

SCENARIO("StateActionPairContainer a storage for state-action pair.",
         "[rl::agent::StateActionPairContainer]") {
  GIVEN("Empty rl::agent::StateActionPairContainer instance") {
    rl::agent::StateActionPairContainer<int, int> container;

    WHEN ("Adding a state-action.") {
      container.addStateAction(rl::agent::StateAction<int, int>(0, 1), 1);
      THEN ("Size should be 1p") {
        REQUIRE(container.getMap().size() == 1);
      }
    }
  }

  GIVEN("Empty rl::agent::StateActionPairContainer") {
    rl::agent::StateActionPairContainer<int, int> container;

    WHEN ("Calling addSate with 5 actions.") {
      container.addState(5, -1, std::set<int>({
        1, 2, 3, 4, 5
      }));
      THEN ("Changes the count to 5.") {
        REQUIRE(container.getMap().size() == 5);
      }
    }
  }

  GIVEN("Empty rl::agent::StateActionPairContainer") {
    rl::agent::StateActionPairContainer<int, int> container;

    WHEN ("Calling addAction with 5 actions.") {
      container.addAction(5, -1, std::set<int>(
        {
          1, 2, 3, 4, 5
        })
      );
      THEN ("Changes the count to 5.") {
        REQUIRE(container.getMap().size() == 5);
      }
    }
  }

  GIVEN("A non-empty rl::agent::StateActionPairContainer") {
    rl::agent::StateActionPairContainer<int, int> container;
    container.addStateAction(rl::agent::StateAction<int, int>(0, 1), 1);

    WHEN ("Calling setStateActionValue.") {
      REQUIRE(container.getStateActionValue(rl::agent::StateAction<int, int>(0, 1)) == 1);
      container.setStateActionValue(rl::agent::StateAction<int, int>(0, 1), 2);
      THEN ("Changes the value of an existing state action.") {
        REQUIRE(container.getStateActionValue(rl::agent::StateAction<int, int>(0, 1)) == 2);
      }
    }
  }
}
