/*
 * Sarsa_test.cpp
 *
 *  Created on: May 31, 2014
 *      Author: jandres
 */

#include <vector>
#include <iostream>

#include "GlobalHeader.h"

#include "UnitTest++.h"
#include "Agent.h"
#include "SensorRandomWalk.h"
#include "ActuatorBase.h"
#include "RandomWalkEnvironment.h"
#include "DynaQET.h"
#include "EpsilonGreedy.h"
#include "Softmax.h"

using std::vector;

using namespace AI;
using namespace std;

TEST(DynaQInitialization) {
  RandomWalkEnvironment rwe;
  SensorRandomWalk srw(rwe);
  srw.addTerminalState(T);
  ActuatorBase<AI::INT, AI::INT> arw(rwe);
  arw.addAction(L);
  arw.addAction(R);
  Algorithm::Policy::EpsilonGreedy<AI::INT, AI::INT> policy(1.0F);
  Algorithm::RL::DynaQET<AI::INT, AI::INT> dynaQAlgorithm(0.1F, 0.9F, policy,
                                                          50, 1.0F, 1.0F, 0.5F);

  Agent<AI::INT, AI::INT> agent(srw, arw, dynaQAlgorithm);

  AI::INT iterationCount = 0;
  for (AI::INT i = 0; i < 10; i++) {
    rwe.reset();
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
