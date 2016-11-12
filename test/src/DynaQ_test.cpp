/*
 * DynaQ_test.cpp
 */

#include "GlobalHeader.h"

#include <iostream>

#include "Agent.h"
#include "SensorRandomWalk.h"
#include "ActuatorBase.h"
#include "RandomWalkEnvironment.h"
#include "DynaQ.h"
#include "EpsilonGreedy.h"
#include "Softmax.h"

#include "catch.hpp"

using std::vector;

using namespace AI;
using namespace std;

SCENARIO("DynaQ converge to a solution", "[Algorithm::RL::DynaQ]") {
  GIVEN("A random walk environment") {
    RandomWalkEnvironment rwe;
    SensorRandomWalk srw(rwe);
    srw.addTerminalState(T);
    ActuatorBase<AI::INT, AI::INT> arw(rwe);
    arw.addAction(L);
    arw.addAction(R);
    Algorithm::Policy::EpsilonGreedy<AI::INT, AI::INT> policy(1.0F);
    Algorithm::RL::DynaQ<AI::INT, AI::INT> dynaQAlgorithm(0.1F, 0.9F, policy, 100,
                                                          1.0F, 1.0F);
    Agent<AI::INT, AI::INT> agent(srw, arw, dynaQAlgorithm);

    WHEN("We do multiple episodes") {
      AI::INT iterationCount = 0;
      for (AI::INT i = 0; i < 10; i++) {
        rwe.reset();

        iterationCount = agent.executeEpisode();

        THEN("At the end, we solve the random walk environment in 2 iteration") {
          REQUIRE(iterationCount <= 2);
        }
      }
    }
  }
}
