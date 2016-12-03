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

using rl::agent::ActionContainerFactory;
using rl::algorithm::SarsaFactory;
using rl::policy::EpsilonGreedyFactory;

SCENARIO("Environment represents the thing agent interacts with.",
         "[rl::agent::AgentSupervised]") {
  GIVEN("A binary environment in which 1 is good and 0 is bad.") {
    rl::spState<int> state0(new int(0));
    rl::spState<int> state1(new int(1));

    rl::spAction<int> action0(new int(0));
    rl::spAction<int> action1(new int(1));

    auto policy = EpsilonGreedyFactory<int, int>(1.0F).get();
    auto sarsaAlgorithm = SarsaFactory<int, int>(0.1F, 0.9F, policy).get();
    auto actionSet = ActionContainerFactory<int>(
      rl::spActionSet<int>({action0, action1})).get();
    rl::agent::AgentSupervised<int, int> supevisedAgent(actionSet,
                                                        sarsaAlgorithm);

    WHEN("When I train 1 to be good and 0 to be bad") {
      // We don't transition anywhere. It's just being in state 1 is good.
      supevisedAgent.train(state1, action1, 1000, state1);

      // Same deal.
      supevisedAgent.train(state0, action0, -1000, state0);

      THEN("Agent should know that 1 should be good and 0 should be bad") {
        auto value1 = sarsaAlgorithm->getStateActionValue(
          rl::agent::StateAction<int, int>(state1, action1));
        auto value0 = sarsaAlgorithm->getStateActionValue(
          rl::agent::StateAction<int, int>(state0, action0));

        REQUIRE(value1 > value0);
      }
    }
  }
}
