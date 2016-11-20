/**
 * Softmax_test.cpp
 */

#include <map>
#include <iostream>
#include <set>

#include "rl"

#include "catch.hpp"

using namespace rl;
using namespace rl::algorithm;
using namespace std;

SCENARIO("Softmax action selection probability increases as the value of the action increases.",
         "[rl::Policy::Softmax]") {
  policy::Softmax<rl::INT, rl::INT> policy(0.9F);

  rl::spState<rl::INT> dummyState(new rl::INT(1));
  rl::spAction<rl::INT> action01(new rl::INT(1));
  rl::spAction<rl::INT> action02(new rl::INT(2));
  rl::spAction<rl::INT> action03(new rl::INT(3));
  rl::spAction<rl::INT> action04(new rl::INT(4));
  spActionSet<rl::INT> actionSet(
    {
      action01, action02, action03, action04
    }
  );

  using StateActionII = StateAction<rl::INT, rl::INT>;

  map<StateAction<rl::INT, rl::INT>, rl::FLOAT> stateActionPairValueMap;
  stateActionPairValueMap[StateActionII(dummyState, action01)] = 1.0F;
  stateActionPairValueMap[StateActionII(dummyState, action02)] = 2.0F;
  stateActionPairValueMap[StateActionII(dummyState, action03)] = -1.0F;
  stateActionPairValueMap[StateActionII(dummyState, action04)] = 2.2F;

  GIVEN("The following action-value map") {
    spActionValueMap<rl::INT> actionValueMap;
    for (auto &action : actionSet) {
      actionValueMap[action] = stateActionPairValueMap.at(StateActionII(dummyState, action));
    }

    rl::UINT action01Ctr(0), action02Ctr(0), action03Ctr(0), action04Ctr(0);
    for (rl::INT i = 0; i < 1000; i++) {
      auto action = policy.getAction(actionValueMap, actionSet);

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
