/*
 * Sarsa_test.cpp
 */

#include "declares.h"

#include <vector>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

#include "Agent.h"
#include "QLearningETGD.h"
#include "EpsilonGreedy.h"
#include "SensorMountainCar.h"
#include "ActuatorBase.h"
#include "MountainCarEnvironment.h"
#include "TileCodeCorrect.h"
#include "TileCodeMurMur.h"
#include "TileCodeMt1993764.h"

#include "catch.hpp"

using std::vector;

using namespace AI;
using namespace AI::Algorithm;
using namespace AI::Algorithm::SL;
using namespace std::chrono;
using namespace std;

SCENARIO("Q-learning Eligibility Traces and Gradient Descent converge to a solution",
         "[Algorithm::RL::QLearingETGD]") {
  GIVEN("A Mountain Car environment") {
    vector<DimensionInfo<AI::FLOAT> > dimensionalInfoVector(
      {
        DimensionInfo<AI::FLOAT>(-1.2F, 0.5F, 10),  // This is the y axis position.
        DimensionInfo<AI::FLOAT>(-0.07F, 0.07F, 10),  // This is the velocity.
        DimensionInfo<AI::FLOAT>(0.0F, 2.0F, 3, 0.0F)  // Actions will be treated discretely.
      });

    // Now that we have the domain information, we feed these to TileCode* object
    // to create a multi-dimensional grid.
    TileCodeCorrect tileCode(dimensionalInfoVector, 10);

    // We will be using the greedy policy for both offline and online policy.
    Policy::EpsilonGreedySL policy(1.0F);

    // We will be using Q-Learning Gradient Descent for learning algorithm.
    QLearningETGD qLearning(tileCode, 0.05F, 1.0F, 0.9F, policy);

    // Instantiate the environment that represent that represent our environment.
    MountainCarEnvironment mce;

    SensorMountainCar smc(mce);  // Instantiate the sensor of our agent.

    // Instantiate the Actuator of our robot, which is "gas pedal".
    ActuatorBase<AI::STATE_CONT, AI::ACTION_CONT> amc(mce);

    // Initialize the possible actions.
    amc.addAction(vector<AI::FLOAT>(1, 0));
    amc.addAction(vector<AI::FLOAT>(1, 1));
    amc.addAction(vector<AI::FLOAT>(1, 2));

    // Initialize the Agent with the Sensor, Actuator and Learning algorithm.
    AgentSL<AI::FLOAT> agent(smc, amc, qLearning);

    WHEN("We do multiple episodes") {
      AI::INT iterationCount = 0;
      for (AI::INT i = 0; i < 1000; i++) {
        mce.reset();

        iterationCount = agent.executeEpisode();
      }

      THEN("At the end, we solve the Mountain Car environment in 100 iteration") {
        REQUIRE(iterationCount <= 100);
      }
    }
  }
}
