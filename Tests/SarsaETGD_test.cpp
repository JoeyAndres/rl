/*
 * Sarsa_test.cpp
 *
 *  Created on: May 31, 2014
 *      Author: jandres
 */

#include "GlobalHeader.h"

#include <vector>
#include <iostream>

#include <ctime>
#include <ratio>
#include <chrono>

#include "UnitTest++.h"
#include "Sarsa.h"
#include "Agent.h"
#include "SarsaETGD.h"
#include "EpsilonGreedy.h"
#include "SensorMountainCar.h"
#include "ActuatorMountainCar.h"
#include "MountainCarEnvironment.h"
#include "TileCodeCorrect.h"
#include "TileCodeMurMur.h"
#include "TileCodeUNH.h"

using std::vector;

using namespace AI;
using namespace AI::Algorithm;
using namespace std::chrono;
using namespace std;

TEST(SarsaETGDInitialization) {
  DimensionInfo<AI::FLOAT> dimensionalInfo[] = { DimensionInfo<AI::FLOAT>(-1.2F,
                                                                          0.5F,
                                                                          10),
      DimensionInfo<AI::FLOAT>(-0.07F, 0.07F, 10), DimensionInfo<AI::FLOAT>(
          0.0F, 2.0F, 3), };

  vector<DimensionInfo<AI::FLOAT> > dimensionalInfoVector(
      dimensionalInfo,
      dimensionalInfo
          + sizeof(dimensionalInfo) / sizeof(DimensionInfo<AI::FLOAT> ));
  dimensionalInfoVector[2].setGeneralizationScale(0.0F);
  TileCodeCorrect tileCode(dimensionalInfoVector, 8);
  EpsilonGreedySL policy(1.0F);
  SarsaETGD sarsa(tileCode, 0.1F, 1.0F, 0.9F, policy);
  SensorMountainCar smc;
  ActuatorMountainCar amc;
  amc.addAction(vector < AI::FLOAT > (1, 0));
  amc.addAction(vector < AI::FLOAT > (1, 1));
  amc.addAction(vector < AI::FLOAT > (1, 2));
  AgentSL<AI::FLOAT> agent(smc, amc, sarsa);
}

TEST(SarsaETGDMountainCar01) {
  DimensionInfo<AI::FLOAT> dimensionalInfo[] = { DimensionInfo<AI::FLOAT>(-1.2F,
                                                                          0.5F,
                                                                          10),
      DimensionInfo<AI::FLOAT>(-0.07F, 0.07F, 10), DimensionInfo<AI::FLOAT>(
          0.0F, 2.0F, 3), };

  vector<DimensionInfo<AI::FLOAT> > dimensionalInfoVector(
      dimensionalInfo,
      dimensionalInfo
          + sizeof(dimensionalInfo) / sizeof(DimensionInfo<AI::FLOAT> ));
  dimensionalInfoVector[2].setGeneralizationScale(0.0F);
  TileCodeCorrect tileCode(dimensionalInfoVector, 8);
  EpsilonGreedySL policy(1.0F);
  SarsaETGD sarsa(tileCode, 0.1F, 1.0F, 0.9F, policy);
  SensorMountainCar smc;
  ActuatorMountainCar amc;
  amc.addAction(vector < AI::FLOAT > (1, 0));
  amc.addAction(vector < AI::FLOAT > (1, 1));
  amc.addAction(vector < AI::FLOAT > (1, 2));
  AgentSL<AI::FLOAT> agent(smc, amc, sarsa);

  AI::INT iterationCount = 0;
  for (AI::INT i = 0; i < 1000; i++) {
    MountainCarEnvironment& mce = MountainCarEnvironment::getInstance();
    mce.reset();

    iterationCount = 0;
    agent.preExecute();
    while (!agent.episodeDone()) {
      iterationCount++;
      agent.execute();
    }
    cout << iterationCount << endl;
    //cout << ".";
    agent.postExecute();
  }
  cout << endl;
  CHECK(iterationCount < 300);
}

int main(void) {
  return UnitTest::RunAllTests();
}
