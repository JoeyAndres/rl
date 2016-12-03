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

#include "RandomWalkEnvironment.h"
#include "SensorRandomWalk.h"

using std::vector;

using rl::policy::EpsilonGreedyFactory;
using rl::agent::ActuatorFactory;
using rl::agent::SensorDiscreteFactory;
using rl::algorithm::SarsaETFactory;

SCENARIO("SarsaET converge to a solution",
         "[rl::SarsaET]") {
  GIVEN("A random walk environment") {
    // Setup actuator with actions.
    auto arw = ActuatorFactory<rl::INT>({ L, R }).get();
    // Setup sensor.
    auto srw = SensorDiscreteFactory<rl::INT>(B).get();
    srw->addTerminalState(T);  // Setup terminal state.

    // Setup environment.
    auto rwe = RandomWalkEnvironmentFactory(arw, srw).get();

    auto policy = EpsilonGreedyFactory<rl::INT, rl::INT>(1.0F).get();
    auto sarsaET =
      SarsaETFactory<rl::INT, rl::INT>(0.1F, 0.9F, policy, 0.2).get();

    rl::agent::Agent <rl::INT, rl::INT> agent(rwe, sarsaET);

    WHEN("We do multiple episodes") {
      rl::INT iterationCount = 0;
      for (rl::INT i = 0; i < 100; i++) {
        agent.reset();  // Overloaded to go back to set b.

        iterationCount = agent.executeEpisode();

        THEN("At the end, we solve the random walk environment in 2 "
               "iteration") {
          REQUIRE(iterationCount <= 2);
        }
      }
    }
  }
}
