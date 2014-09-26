/*
 * DynaQPrioritizeSweeping_test.cpp
 *
 *  Created on: May 31, 2014
 *      Author: jandres
 */

#include "GlobalHeader.h"

#include <vector>
#include <iostream>

#include "UnitTest++.h"
#include "Agent.h"
#include "SensorRandomWalk.h"
#include "ActuatorRandomWalk.h"
#include "RandomWalkEnvironment.h"
#include "DynaQPrioritizedSweeping.h"
#include "EpsilonGreedy.h"
#include "Softmax.h"

using std::vector;

using namespace AI;
using namespace std;

TEST(DynaQInitialization) {
  SensorRandomWalk<AI::INT> srw;
  srw.addTerminalState(T);
  ActuatorRandomWalk<AI::INT> arw;
  arw.addAction(L);
  arw.addAction(R);
  Algorithm::EpsilonGreedy<AI::INT, AI::INT> policy(1.0F);
  Algorithm::DynaQPrioritizeSweeping<AI::INT, AI::INT> dynaQAlgorithm(0.1F, 0.9F,
															  policy, 20, 1.0F,
															  1.0F, 0.1F);

  Agent<AI::INT, AI::INT> agent(srw, arw, dynaQAlgorithm);

  AI::INT iterationCount = 0;
  for (AI::INT i = 0; i < 10; i++) {
	RandomWalkEnvironment& instance = RandomWalkEnvironment::getInstance();
	instance.reset();
	iterationCount = 0;
	agent.preExecute();
	while (!agent.episodeDone()) {
	  iterationCount++;
	  agent.execute();
	}
	agent.postExecute();
  }
  CHECK(iterationCount == 2);
}

TEST(DynaQSoftmaxPolicy) {
  SensorRandomWalk<AI::INT> srw;
  srw.addTerminalState(T);
  ActuatorRandomWalk<AI::INT> arw;
  arw.addAction(L);
  arw.addAction(R);
  Algorithm::Softmax<AI::INT, AI::INT> policy(0.1F);
  Algorithm::DynaQPrioritizeSweeping<AI::INT, AI::INT> dynaQAlgorithm(0.1F, 0.9F,
															  policy, 50, 1.0F,
															  1.0F, 0.1F);

  Agent<AI::INT, AI::INT> agent(srw, arw, dynaQAlgorithm);

  AI::INT iterationCount = 0;
  for (AI::INT i = 0; i < 10; i++) {
	RandomWalkEnvironment& instance = RandomWalkEnvironment::getInstance();
	instance.reset();
	iterationCount = 0;
	agent.preExecute();
	while (!agent.episodeDone()) {
	  iterationCount++;
	  agent.execute();
	}
#ifdef TEST_PRINT
	cout << iterationCount << endl;
#endif
	agent.postExecute();
  }
  CHECK(iterationCount == 2);
}

int main(void) {
  return UnitTest::RunAllTests();
}
