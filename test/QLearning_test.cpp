/*
 * Sarsa_test.cpp
 *
 *  Created on: May 31, 2014
 *      Author: jandres
 */

#include <vector>
#include <iostream>

#include "UnitTest++.h"
#include "Agent.h"
#include "SensorRandomWalk.h"
#include "ActuatorBase.h"
#include "RandomWalkEnvironment.h"
#include "QLearning.h"
#include "EpsilonGreedy.h"

using std::vector;

using namespace AI;
using namespace AI::Algorithm;
using namespace AI::Algorithm::RL;
using namespace std;

TEST(QLearningInitialization) {
  RandomWalkEnvironment rwEnv;
  SensorRandomWalk srw(rwEnv);
  srw.addTerminalState(T);
  ActuatorBase<AI::INT, AI::INT>arw(rwEnv);
  arw.addAction(L);
  arw.addAction(R);
  Policy::EpsilonGreedy<AI::INT, AI::INT> policy(1.0F);
  QLearning<AI::INT, AI::INT> qlearningAlgorithm(0.1F, 0.9F, policy);

  Agent<AI::INT, AI::INT> agent(srw, arw, qlearningAlgorithm);

  AI::INT iterationCount = 0;
  for (AI::INT i = 0; i < 100; i++) {
    rwEnv.reset();

    iterationCount = 0;
    agent.preExecute();
    while (!agent.episodeDone()) {
      iterationCount++;
      agent.execute();
    }
    agent.postExecute();
  }
  CHECK(iterationCount <= 2);
}

int main(void) {
  return UnitTest::RunAllTests();
}
