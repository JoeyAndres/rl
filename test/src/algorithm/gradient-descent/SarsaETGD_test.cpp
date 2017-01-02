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

#include <array>

#include "catch.hpp"
#include "rl"

#include "MountainCarEnvironment.h"
#include "SensorMountainCar.h"

using std::array;

using rl::policy::EpsilonGreedyFactory;
using rl::agent::ActuatorFactory;
using rl::algorithm::SarsaETGDFactory;
using rl::coding::TileCodeCorrectFactory;

SCENARIO("Sarsa Eligibility Traces and Gradient Descent converge to a "
           "solution",
         "[rl::SarsaETGD]") {
  GIVEN("A Mountain Car environment") {
    rl::spFloatArray<1> reverse(new rl::floatArray<1>({0}));
    rl::spFloatArray<1> neutral(new rl::floatArray<1>({1}));
    rl::spFloatArray<1> forward(new rl::floatArray<1>({2}));

    auto amc = ActuatorFactory<rl::floatArray<1>>(
      rl::spActionSet<rl::floatArray<1>>(
        {
          reverse,
          neutral,
          forward
        })).get();
    // Setup sensor.
    auto smc = SensorMountainCarFactory::create();
    // Setup environment.
    auto mce = MountainCarEnvironmentFactory(amc, smc).get();

    auto policy =
      EpsilonGreedyFactory<rl::floatArray<2>, rl::floatArray<1>>(1.0F).get();

    // Setup tile coding.
    array<rl::coding::DimensionInfo<rl::FLOAT>, 3> dimensionalInfoVector = {
      rl::coding::DimensionInfo<rl::FLOAT>(-1.2F, 0.5F, 10),  // Velocity.
      rl::coding::DimensionInfo<rl::FLOAT>(-0.07F, 0.07F, 10),  // Position.

      // Action dimension.
      rl::coding::DimensionInfo<rl::FLOAT>(0.0F, 2.0F, 3, 0.0F)
    };

    WHEN("We do multiple episodes with Default weight container (vector)") {
      // Setup tile coding with 8 offsets.
      auto tileCode = TileCodeCorrectFactory<3, 8>(dimensionalInfoVector).get();
      auto sarsa =
        SarsaETGDFactory<3, 8>(tileCode, 0.1F, 1.0F, 0.9F, policy).get();
      rl::agent::AgentGD<3> agent(mce, sarsa);

      rl::INT iterationCount = 0;
      for (rl::INT i = 0; i < 1000; i++) {
        agent.reset();

        iterationCount = agent.executeEpisode();
      }

      THEN("At the end, we solve the Mountain Car environment in 100 "
             "iteration") {
        REQUIRE(iterationCount <= 100);
      }
    }
  }
}
