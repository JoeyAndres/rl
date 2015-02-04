/**
 * Sarsa_test.cpp
 */

#include <vector>
#include <iostream>
#include <cppunit/TestAssert.h>

#include "Sarsa_test.h"
#include "Sarsa.h"
#include "Agent.h"
#include "SensorRandomWalk.h"
#include "ActuatorBase.h"
#include "RandomWalkEnvironment.h"
#include "EpsilonGreedy.h"

using std::vector;

using namespace AI;
using namespace std;

void Sarsa_test::episodeTest(){
  RandomWalkEnvironment rwe;
  SensorRandomWalk srw(rwe);
  srw.addTerminalState(T);
  ActuatorBase<AI::INT, AI::INT> arw(rwe);
  arw.addAction(L);
  arw.addAction(R);
  Algorithm::Policy::EpsilonGreedy<AI::INT, AI::INT> policy(1.0F);
  Algorithm::RL::Sarsa<AI::INT, AI::INT> sarsaAlgorithm(0.1F, 0.9F, policy);

  Agent<AI::INT, AI::INT> agent(srw, arw, sarsaAlgorithm);

  AI::INT iterationCount = 0;
  for (AI::INT i = 0; i < 100; i++) {
    rwe.reset();

    iterationCount = agent.executeEpisode();
  }
  CPPUNIT_ASSERT(iterationCount <= 2);
}
