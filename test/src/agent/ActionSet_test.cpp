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
    rl::spAction<rl::INT> action1(new rl::INT(1));
    rl::spAction<rl::INT> action2(new rl::INT(2));
    rl::spAction<rl::INT> action3(new rl::INT(3));
    rl::spAction<rl::INT> action4(new rl::INT(4));

    ActionSet<rl::INT> as(rl::spActionSet<rl::INT>({ action1, action2, action3, action4 }));

    WHEN ("I first access action.") {
      auto actions = as.getActionSet();
      THEN ("It should return 4") {
        REQUIRE(actions.size() == 4);
      }
    }
  }
}
