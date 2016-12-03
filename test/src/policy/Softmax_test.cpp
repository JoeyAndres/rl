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

#include <map>
#include <iostream>
#include <set>

#include "rl"
#include "catch.hpp"

using rl::policy::SoftmaxFactory;

SCENARIO("Softmax action selection probability increases as the value of the "
           "action increases.",
         "[rl::Policy::Softmax]") {
  auto policy = SoftmaxFactory<rl::INT, rl::INT>(0.9F).get();

  rl::spState<rl::INT> dummyState(new rl::INT(1));
  rl::spAction<rl::INT> action01(new rl::INT(1));
  rl::spAction<rl::INT> action02(new rl::INT(2));
  rl::spAction<rl::INT> action03(new rl::INT(3));
  rl::spAction<rl::INT> action04(new rl::INT(4));
  rl::spActionSet<rl::INT> actionSet(
    {
      action01, action02, action03, action04
    });

  using StateActionII = StateAction<rl::INT, rl::INT>;

  map<StateAction<rl::INT, rl::INT>, rl::FLOAT> stateActionPairValueMap;
  stateActionPairValueMap[StateActionII(dummyState, action01)] = 1.0F;
  stateActionPairValueMap[StateActionII(dummyState, action02)] = 2.0F;
  stateActionPairValueMap[StateActionII(dummyState, action03)] = -1.0F;
  stateActionPairValueMap[StateActionII(dummyState, action04)] = 2.2F;

  GIVEN("The following action-value map") {
    rl::spActionValueMap<rl::INT> actionValueMap;
    for (auto &action : actionSet) {
      actionValueMap[action] = stateActionPairValueMap.at(
        StateActionII(dummyState, action));
    }

    rl::UINT action01Ctr(0), action02Ctr(0), action03Ctr(0), action04Ctr(0);
    for (rl::INT i = 0; i < 1000; i++) {
      auto action = policy->getAction(actionValueMap, actionSet);

      if (*action == *action01) {
        action01Ctr++;
      } else if (*action == *action02) {
        action02Ctr++;
      } else if (*action == *action03) {
        action03Ctr++;
      } else if (*action == *action04) {
        action04Ctr++;
      } else {
        assert(false);
      }
    }

    REQUIRE(action01Ctr > action03Ctr);
    REQUIRE(action02Ctr > action01Ctr);
    REQUIRE(action04Ctr > action02Ctr);
  }
}
