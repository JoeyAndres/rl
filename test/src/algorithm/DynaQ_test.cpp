/*
 * DynaQ_test.cpp
 */

#include <iostream>

#include "rl"

#include "../../lib/catch.hpp"

#include "RandomWalkEnvironment.h"
#include "SensorRandomWalk.h"

using std::vector;

using namespace std;

SCENARIO("DynaQ converge to a solution", "[rl::DynaQ]") {
  GIVEN("A random walk environment") {
    rl::agent::Actuator <rl::INT> arw(rl::spActionSet<rl::INT>({ L, R }));  // Setup actuator with actions.
    rl::SensorRandomWalk srw;
    srw.addTerminalState(T);

    rl::RandomWalkEnvironment rwe(arw, srw);

    rl::policy::EpsilonGreedy <rl::INT, rl::INT> policy(1.0F);
    rl::algorithm::DynaQ <rl::INT, rl::INT> dynaQAlgorithm(0.1F, 0.9F, policy, 100,
                                                           1.0F, 1.0F);
    rl::agent::Agent <rl::INT, rl::INT> agent(rwe, dynaQAlgorithm);

    WHEN("We do multiple episodes") {
      rl::INT iterationCount = 0;
      for (rl::INT i = 0; i < 10; i++) {
        agent.reset();

        iterationCount = agent.executeEpisode();

        THEN("At the end, we solve the random walk environment in 2 iteration") {
          REQUIRE(iterationCount <= 2);
        }
      }
    }
  }
}
