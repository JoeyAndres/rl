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
  DimensionInfo<AI::FLOAT> dimensionalInfo[] = {
    DimensionInfo<AI::FLOAT>(-1.2F, 0.5F, 10),
    DimensionInfo<AI::FLOAT>(-0.07F, 0.07F, 10),
    DimensionInfo<AI::FLOAT>(0.0F, 2.0F, 3),
  };

  vector<DimensionInfo<AI::FLOAT> > dimensionalInfoVector(
      dimensionalInfo,
      dimensionalInfo +
      sizeof(dimensionalInfo) / sizeof(DimensionInfo<AI::FLOAT> ));
  
  dimensionalInfoVector[2].setGeneralizationScale(0.0F);
  TileCodeCorrect tileCode(dimensionalInfoVector, 8);
  Policy::EpsilonGreedySL policy(1.0F);
  QLearningETGD qLearning(tileCode, 0.1F, 1.0F, 0.9F, policy);
  MountainCarEnvironment mce;
  SensorMountainCar smc(mce);
  ActuatorBase<AI::STATE_CONT, AI::ACTION_CONT > amc(mce);
  amc.addAction(vector <AI::FLOAT > (1, 0));
  amc.addAction(vector < AI::FLOAT > (1, 1));
  amc.addAction(vector < AI::FLOAT > (1, 2));
  AgentSL<AI::FLOAT> agent(smc, amc, qLearning);

  AI::INT iterationCount = 0;
  for (AI::INT i = 0; i < 1000; i++) {    
    mce.reset();

    iterationCount = 0;
    agent.preExecute();
    while (!agent.episodeDone()) {
      iterationCount++;
      agent.execute();
    }
    agent.postExecute();
  }
  CPPUNIT_ASSERT(iterationCount < 300);
}