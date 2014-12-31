/*
 * DynaQ_test.cpp
 */

#include "GlobalHeader.h"

#include <vector>
#include <iostream>
#include <cppunit/TestAssert.h>

#include "DynaQ_test.h"
#include "Agent.h"
#include "SensorRandomWalk.h"
#include "ActuatorBase.h"
#include "RandomWalkEnvironment.h"
#include "DynaQ.h"
#include "EpsilonGreedy.h"
#include "Softmax.h"

using std::vector;

using namespace AI;
using namespace std;

void DynaQ_test::episodeTest(){
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
  CPPUNIT_ASSERT(iterationCount <= 2);
}