//
// Created by jandres on 12/11/16.
//

#include "rl"

#include <iostream>

#include "SensorRandomWalk.h"
#include "RandomWalkEnvironment.h"

#include "../../lib/catch.hpp"

using namespace std;

SCENARIO("Agent interacts with the environment as expected.",
         "[rl::agent::Agent]") {
  GIVEN("A binary environment in which 1 is good and 0 is bad.") {
    rl::agent::Actuator<rl::INT> arw(
      {
        rl::RandomWalkEnvironment::Action::L,
        rl::RandomWalkEnvironment::Action::R
      }
    );
    rl::SensorRandomWalk srw;
    srw.addTerminalState(rl::RandomWalkEnvironment::State::T);

    rl::RandomWalkEnvironment rwe(arw, srw);

    rl::policy::EpsilonGreedy<rl::INT, rl::INT> policy(1.0F);
    rl::algorithm::DynaQ<rl::INT, rl::INT> dynaQAlgorithm(
      0.1F, 0.9F, policy, 100, 1.0F, 1.0F);
    rl::agent::Agent<rl::INT, rl::INT> agent(rwe, dynaQAlgorithm);

    WHEN ("When I move left.") {
      REQUIRE(agent.getLastObservedState() == rl::RandomWalkEnvironment::State::B);
      agent.applyAction(rl::RandomWalkEnvironment::Action::L);
      THEN ("I move from B to A.") {
        REQUIRE(agent.getLastObservedState() == rl::RandomWalkEnvironment::State::A);
      }
    }
  }
}
