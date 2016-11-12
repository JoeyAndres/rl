/**
 * Sarsa_test.cpp
 */

#include <vector>
#include <iostream>

#include "Sarsa.h"
#include "Agent.h"
#include "SensorRandomWalk.h"
#include "ActuatorBase.h"
#include "RandomWalkEnvironment.h"
#include "EpsilonGreedy.h"

#include "catch.hpp"

using std::vector;

using namespace AI;
using namespace std;

SCENARIO("Sarsa converge to a solution",
         "[Algorithm::RL::Sarsa]") {
  GIVEN("A random walk environment") {
    RandomWalkEnvironment rwe;
    SensorRandomWalk srw(rwe);
    srw.addTerminalState(T);
    ActuatorBase<AI::INT, AI::INT> arw(rwe);
    arw.addAction(L);
    arw.addAction(R);
    Algorithm::Policy::EpsilonGreedy<AI::INT, AI::INT> policy(1.0F);
    Algorithm::RL::Sarsa<AI::INT, AI::INT> sarsaAlgorithm(0.1F, 0.9F, policy);

    Agent<AI::INT, AI::INT> agent(srw, arw, sarsaAlgorithm);

    WHEN("We do multiple episodes") {
      AI::INT iterationCount = 0;
      for (AI::INT i = 0; i < 100; i++) {
        rwe.reset();

        THEN("At the end, we solve the random walk environment in 2 iteration") {
          REQUIRE(iterationCount <= 2);
        }
      }
    }
  }
}
