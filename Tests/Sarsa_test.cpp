/*
 * Sarsa_test.cpp
 *
 *  Created on: May 31, 2014
 *      Author: jandres
 */

#include <vector>
#include <iostream>

#include "UnitTest++.h"
#include "Sarsa.h"
#include "Agent.h"
#include "SensorRandomWalk.h"
#include "ActuatorRandomWalk.h"
#include "RandomWalkEnvironment.h"
#include "EpsilonGreedy.h"

using std::vector;

using namespace AI;
using namespace std;

TEST(SarsaInitialization) {
  SensorRandomWalk<AI::INT> srw;
  srw.addTerminalState(T);
  ActuatorRandomWalk<AI::INT> arw;
  arw.addAction(L);
  arw.addAction(R);
  Algorithm::EpsilonGreedy<AI::INT, AI::INT> policy(1.0F);
  Algorithm::Sarsa<AI::INT, AI::INT> sarsaAlgorithm(0.1F, 0.9F, policy);

  Agent<AI::INT, AI::INT> agent(srw, arw, sarsaAlgorithm);

  AI::INT iterationCount = 0;
  for (AI::INT i = 0; i < 100; i++) {
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

int main(void) {
  return UnitTest::RunAllTests();
}
