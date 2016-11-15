//
// Created by jandres on 12/11/16.
//

#include "rl"

#include "../../lib/catch.hpp"

using namespace rl;
using namespace std;

SCENARIO("Agent have a storage for actions.",
         "[rl::agent::ActionSet]") {
  GIVEN("ActionSet instance from no-arg constructor.") {
    rl::agent::ActionSet<rl::INT> asNoArg;

    WHEN ("I first access action.") {
      auto actions = asNoArg.getActionSet();
      THEN ("It is empty.") {
        REQUIRE(actions.size() == 0);
      }
    }
  }

  GIVEN("ActionSet instance with some actions initialize.") {
    ActionSet<rl::INT> as({ 1, 2, 3, 4 });

    WHEN ("I first access action.") {
      auto actions = as.getActionSet();
      THEN ("It should return 4") {
        REQUIRE(actions.size() == 4);
      }
    }
  }
}
