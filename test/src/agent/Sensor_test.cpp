//
// Created by jandres on 12/11/16.
//

#include "rl"

#include <iostream>

#include "SensorRandomWalk.h"
#include "RandomWalkEnvironment.h"

#include "../../lib/catch.hpp"

using namespace std;

SCENARIO("Sensor for representing the states in the environment.",
         "[rl::agent::Sensor]") {
  GIVEN("Sensor instance") {
    rl::agent::Actuator<rl::INT> arw({ L, R });
    rl::SensorRandomWalk srw;
    srw.addTerminalState(T);

    rl::RandomWalkEnvironment rwe(arw, srw);

    rl::policy::EpsilonGreedy<rl::INT, rl::INT> policy(1.0F);
    rl::algorithm::DynaQ<rl::INT, rl::INT> dynaQAlgorithm(
      0.1F, 0.9F, policy, 100, 1.0F, 1.0F);
    rl::agent::Agent<rl::INT, rl::INT> agent(rwe, dynaQAlgorithm);

    WHEN ("When I move left.") {
      REQUIRE(*(srw.getLastObservedState()) == *B);
      agent.applyAction(L);
      THEN ("I move from B to A.") {
        REQUIRE(*(srw.getLastObservedState()) == *A);
      }
    }
  }
}
