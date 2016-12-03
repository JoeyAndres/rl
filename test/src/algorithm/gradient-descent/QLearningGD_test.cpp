/**
 * rl - Reinforcement Learning
 * Copyright (C) 2016  Joey Andres<yeojserdna@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <vector>

#include "catch.hpp"
#include "rl"

#include "MountainCarEnvironment.h"
#include "SensorMountainCar.h"

using std::vector;

using rl::policy::EpsilonGreedyFactory;
using rl::agent::ActuatorFactory;
using rl::algorithm::QLearningGDFactory;
using rl::coding::TileCodeCorrectFactory;

SCENARIO("Q-learning Gradient Descent converge to a solution",
         "[rl::QLearingGD]") {
  GIVEN("A Mountain Car environment") {
    // Actions.
    rl::spActionCont reverse(new rl::actionCont({0}));
    rl::spActionCont neutral(new rl::actionCont({1}));
    rl::spActionCont forward(new rl::actionCont({2}));

    auto amc = ActuatorFactory<rl::actionCont>(
      rl::spActionSet<rl::actionCont>(
        {
          reverse,
          neutral,
          forward
        })).get();
    auto smc = SensorMountainCarFactory::create();  // Setup sensor.
    auto mce = MountainCarEnvironmentFactory(amc, smc).get();

    auto policy =
      EpsilonGreedyFactory<rl::stateCont, rl::actionCont>(1.0F).get();

    // Setup tile coding.
    vector <rl::coding::DimensionInfo<rl::FLOAT>> dimensionalInfoVector = {
      rl::coding::DimensionInfo<rl::FLOAT>(-1.2F, 0.5F, 7),  // Velocity.
      rl::coding::DimensionInfo<rl::FLOAT>(-0.07F, 0.07F, 7),  // Position.

      // Action dimension.
      rl::coding::DimensionInfo<rl::FLOAT>(0.0F, 2.0F, 3, 0.0F)
    };

    // Setup tile coding with 8 offsets.
    auto tileCode = TileCodeCorrectFactory(dimensionalInfoVector, 8).get();
    auto qLearning =
      rl::algorithm::QLearningETGDFactory(
        tileCode, 0.1F, 1.0F, 0.9F, policy).get();
    rl::agent::AgentSL <rl::FLOAT> agent(mce, qLearning);

    WHEN("We do multiple episodes") {
      rl::INT iterationCount = 0;
      for (rl::INT i = 0; i < 1000; i++) {
        mce.reset();

        iterationCount = agent.executeEpisode();
      }

      THEN("At the end, we solve the Mountain Car environment in 100 "
             "iteration") {
        REQUIRE(iterationCount <= 100);
      }
    }
  }
}
