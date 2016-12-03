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

#include "catch.hpp"

#include "rl"
#include "SensorRandomWalk.h"
#include "RandomWalkEnvironment.h"

using rl::policy::EpsilonGreedyFactory;
using rl::agent::ActuatorFactory;
using rl::agent::SensorDiscreteFactory;
using rl::algorithm::DynaQFactory;

SCENARIO("Sensor for representing the states in the environment.",
         "[rl::agent::Sensor]") {
  GIVEN("Sensor instance") {
    // Setup actuator with actions.
    auto arw = ActuatorFactory<rl::INT>({ L, R }).get();
    // Setup sensor.
    auto srw = SensorDiscreteFactory<rl::INT>(B).get();
    srw->addTerminalState(T);  // Setup terminal state.

    // Setup environment.
    auto rwe = RandomWalkEnvironmentFactory(arw, srw).get();

    auto policy =
      EpsilonGreedyFactory<rl::INT, rl::INT>(1.0F).get();
    auto dynaQAlgorithm = DynaQFactory<rl::INT, rl::INT>(
      0.1F, 0.9F, policy, 100, 1.0F, 1.0F).get();
    rl::agent::Agent<rl::INT, rl::INT> agent(rwe, dynaQAlgorithm);

    WHEN("When I move left.") {
      REQUIRE(*(srw->getLastObservedState()) == *B);
      agent.applyAction(L);
      THEN("I move from B to A.") {
        REQUIRE(*(srw->getLastObservedState()) == *A);
      }
    }
  }
}
