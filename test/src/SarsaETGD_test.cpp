/*
 * SarsaETGD_test.cpp
 */

#include "GlobalHeader.h"

#include <vector>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <cppunit/TestAssert.h>

#include "SarsaETGD_test.h"
#include "Sarsa.h"
#include "Agent.h"
#include "SarsaETGD.h"
#include "EpsilonGreedy.h"
#include "SensorMountainCar.h"
#include "ActuatorBase.h"
#include "MountainCarEnvironment.h"
#include "TileCodeCorrect.h"
#include "TileCodeMurMur.h"
#include "TileCodeUNH.h"

using std::vector;

using namespace AI;
using namespace AI::Algorithm;
using namespace AI::Algorithm::SL;
using namespace std::chrono;
using namespace std;

void SarsaETGD_test::episodeTest(){
  vector<DimensionInfo<AI::FLOAT> > dimensionalInfoVector = {
    DimensionInfo<AI::FLOAT>(-1.2F, 0.5F, 7),
    DimensionInfo<AI::FLOAT>(-0.07F, 0.07F, 7),
    DimensionInfo<AI::FLOAT>(0.0F, 2.0F, 3, 0.0F),
  };
  
  TileCodeCorrect tileCode(dimensionalInfoVector, 8);
  Policy::EpsilonGreedySL policy(1.0F);
  SarsaETGD sarsa(tileCode, 0.1F, 1.0F, 0.70F, policy);
  MountainCarEnvironment mce;
  SensorMountainCar smc(mce);
  ActuatorBase<AI::STATE_CONT, AI::ACTION_CONT > amc(mce);
  amc.addAction(vector <AI::FLOAT > (1, 0));
  amc.addAction(vector <AI::FLOAT > (1, 1));
  amc.addAction(vector <AI::FLOAT > (1, 2));
  AgentSL<AI::FLOAT> agent(smc, amc, sarsa);
  
  AI::INT iterationCount = 0;
  for (AI::INT i = 0; i < 1000; i++) {
    mce.reset();
    
    iterationCount = agent.executeEpisode();
  }
  CPPUNIT_ASSERT(iterationCount < 100);
}
