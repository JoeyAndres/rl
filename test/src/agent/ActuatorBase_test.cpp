//
// Created by jandres on 12/11/16.
//

#include "rl"

#include "SensorRandomWalk.h"
#include "RandomWalkEnvironment.h"
#include "../../lib/catch.hpp"

using namespace std;

SCENARIO("Agent have a storage for actions and actuator.",
         "[rl::agent::Actuator]") {
  GIVEN("Actuator") {
    rl::agent::Actuator<rl::INT> actuator(
      {
        rl::RandomWalkEnvironment::Action::L,
        rl::RandomWalkEnvironment::Action::R
      }
    );
    rl::SensorRandomWalk srw;
    srw.addTerminalState(rl::RandomWalkEnvironment::State::T);

    rl::RandomWalkEnvironment rwe(actuator, srw);

    WHEN ("I first access action.") {
      auto actions = actuator.getActionSet();
      THEN ("It is empty.") {
        REQUIRE(actions.size() == 2);
      }
    }
  }
}
