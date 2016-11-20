/*
 * SarsaETGD_test.cpp
 */

#include <vector>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

#include "rl"

#include "../../../lib/catch.hpp"

#include "MountainCarEnvironment.h"
#include "SensorMountainCar.h"

using std::vector;

using namespace std::chrono;
using namespace std;

SCENARIO("Sarsa Eligibility Traces and Gradient Descent converge to a solution",
         "[rl::SarsaETGD]") {
  GIVEN("A Mountain Car environment") {
    // Actions.
    rl::agent::Actuator <rl::stateCont> amc(
      nrl::spActionSet<rl::actionCont>(
        {
          {0},  // Reverse.
          {1},  // Neutral.
          {2}   // Forward.
        }
      )
    );
    rl::SensorMountainCar smc;  // Setup sensor.
    rl::MountainCarEnvironment mce(amc, smc);  // Setup environment.

    rl::policy::EpsilonGreedySL policy(1.0F);

    // Setup tile coding.
    vector <rl::coding::DimensionInfo<rl::FLOAT>> dimensionalInfoVector = {
      rl::coding::DimensionInfo<rl::FLOAT>(-1.2F, 0.5F, 20),  // Velocity.
      rl::coding::DimensionInfo<rl::FLOAT>(-0.07F, 0.07F, 20),  // Position.
      rl::coding::DimensionInfo<rl::FLOAT>(0.0F, 2.0F, 3, 0.0F),  // Action dimension.
    };
    rl::coding::TileCodeCorrect tileCode(dimensionalInfoVector, 20);  // Setup tile coding with 10 offsets.
    rl::algorithm::SarsaETGD sarsa(tileCode, 0.1F, 1.0F, 0.9F, policy);
    rl::agent::AgentSL <rl::FLOAT> agent(mce, sarsa);

    WHEN("We do multiple episodes") {
      rl::INT iterationCount = 0;
      for (rl::INT i = 0; i < 1000; i++) {
        agent.reset();

        iterationCount = agent.executeEpisode();
      }
      THEN("At the end, we solve the Mountain Car environment in 100 iteration") {
        REQUIRE(iterationCount <= 100);
      }
    }
  }
}
