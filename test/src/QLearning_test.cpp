/**
 * QLearning_test.cpp
 */

#include <vector>
#include <iostream>

#include "Agent.h"
#include "SensorRandomWalk.h"
#include "ActuatorBase.h"
#include "RandomWalkEnvironment.h"
#include "QLearning.h"
#include "EpsilonGreedy.h"

#include "catch.hpp"

using std::vector;

using namespace AI;
using namespace AI::Algorithm;
using namespace AI::Algorithm::RL;
using namespace std;

SCENARIO("Q-Learning converge to a solution",
         "[Algorithm::RL::QLearning]") {
  GIVEN("A random walk environment") {
    RandomWalkEnvironment rwEnv;
    SensorRandomWalk srw(rwEnv);
    srw.addTerminalState(T);
    ActuatorBase<AI::INT, AI::INT> arw(rwEnv);
    arw.addAction(L);
    arw.addAction(R);
    Policy::EpsilonGreedy<AI::INT, AI::INT> policy(1.0F);
    QLearning<AI::INT, AI::INT> qlearningAlgorithm(0.1F, 0.9F, policy);

    Agent<AI::INT, AI::INT> agent(srw, arw, qlearningAlgorithm);

    WHEN("We do multiple episodes") {
      AI::INT iterationCount = 0;
      for (AI::INT i = 0; i < 100; i++) {
        rwEnv.reset();

        iterationCount = agent.executeEpisode();

        THEN("At the end, we solve the random walk environment in 2 iteration") {
          REQUIRE(iterationCount <= 2);
        }
      }
    }
  }
}
