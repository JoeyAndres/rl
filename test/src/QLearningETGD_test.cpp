/*
 * Sarsa_test.cpp
 */

#include "GlobalHeader.h"

#include <vector>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <cppunit/TestAssert.h>

#include "QLearningETGD_test.h"
#include "Agent.h"
#include "QLearningETGD.h"
#include "EpsilonGreedy.h"
#include "SensorMountainCar.h"
#include "ActuatorBase.h"
#include "MountainCarEnvironment.h"
#include "TileCodeCorrect.h"
#include "TileCodeMurMur.h"
#include "TileCodeMt1993764.h"

using std::vector;

using namespace AI;
using namespace AI::Algorithm;
using namespace AI::Algorithm::SL;
using namespace std::chrono;
using namespace std;

void QLearningETGD_test::episodeTest(){
  vector<DimensionInfo<AI::FLOAT> > dimensionalInfoVector({
      DimensionInfo<AI::FLOAT>(-1.2F, 0.5F, 10),  // This is the y axis position.
      DimensionInfo<AI::FLOAT>(-0.07F, 0.07F, 10),  // This is the velocity.
      DimensionInfo<AI::FLOAT>(0.0F, 2.0F, 3, 0.0F)});  // Actions will be treated discretely.

  // Now that we have the domain information, we feed these to TileCode* object
  // to create a multi-dimensional grid.
  TileCodeCorrect tileCode(dimensionalInfoVector, 8);

  // We will be using the greedy policy for both offline and online policy.
  Policy::EpsilonGreedySL policy(1.0F);

  // We will be using Q-Learning Gradient Descent for learning algorithm.
  QLearningETGD qLearning(tileCode, 0.1F, 1.0F, 0.9F, policy);

  // Instantiate the environment that represent that represent our environment.
  MountainCarEnvironment mce;  

  SensorMountainCar smc(mce);  // Instantiate the sensor of our agent.

  // Instantiate the Actuator of our robot, which is "gas pedal".
  ActuatorBase<AI::STATE_CONT, AI::ACTION_CONT > amc(mce);

  // Initialize the possible actions. 
  amc.addAction(vector <AI::FLOAT > (1, 0));
  amc.addAction(vector < AI::FLOAT > (1, 1));
  amc.addAction(vector < AI::FLOAT > (1, 2));

  // Initialize the Agent with the Sensor, Actuator and Learning algorithm.
  AgentSL<AI::FLOAT> agent(smc, amc, qLearning);

  // Execute 1000 episodes.
  AI::INT iterationCount = 0;
  for (AI::INT i = 0; i < 100; i++) {    
    mce.reset();

    iterationCount = agent.executeEpisode();
    //#ifdef DEBUG_OUT
    cout << iterationCount << endl;
    //#endif
  }

  // We should've optimize for less than 100 iteration per episode when.
  CPPUNIT_ASSERT(iterationCount < 100);
}
