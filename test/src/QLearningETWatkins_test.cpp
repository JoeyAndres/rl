/*
 * Sarsa_test.cpp
 */

#include <vector>
#include <iostream>

#include "Agent.h"
#include "SensorRandomWalk.h"
#include "ActuatorBase.h"
#include "RandomWalkEnvironment.h"
#include "QLearningET.h"
#include "EpsilonGreedy.h"
#include "Softmax.h"

#include "catch.hpp"

using std::vector;

using namespace AI;
using namespace std;

SCENARIO("Q-learning Eligibility Traces converge to a solution",
         "[Algorithm::RL::QLearningET]") {
  GIVEN("A Random Walk environment") {
    RandomWalkEnvironment rwe;
    SensorRandomWalk srw(rwe);
    srw.addTerminalState(T);
    ActuatorBase<AI::INT, AI::INT> arw(rwe);
    arw.addAction(L);
    arw.addAction(R);
    Algorithm::Policy::EpsilonGreedy<AI::INT, AI::INT> policy(1.0F);
    Algorithm::RL::QLearningET<AI::INT, AI::INT> qlearningAlgorithm(0.1F, 0.9F,
                                                                    policy, 0.5);

    Agent<AI::INT, AI::INT> agent(srw, arw, qlearningAlgorithm);

    WHEN("We do multiple episodes") {
      AI::INT iterationCount = 0;
      for (AI::INT i = 0; i < 100; i++) {
        rwe.reset();

        iterationCount = agent.executeEpisode();
      }

      THEN("At the end, we solve the Random Walk environment in 100 iteration") {
        REQUIRE(iterationCount <= 100);
      }
    }
  }
}
