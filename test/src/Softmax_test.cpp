/**
 * Softmax_test.cpp
 */

#include <map>
#include <iostream>
#include <set>

#include "Softmax.h"

#include "catch.hpp"

using namespace AI;
using namespace AI::Algorithm;
using namespace std;

SCENARIO("Softmax action selection probability increases as the value of the action increases.",
         "[AI::Policy::Softmax]") {
  Policy::Softmax<AI::INT, AI::INT> policy(0.9F);

  AI::INT dummyState(1);
  AI::INT action01(1);
  AI::INT action02(2);
  AI::INT action03(3);
  AI::INT action04(4);
  set<AI::INT> actionSet;
  actionSet.insert(action01);
  actionSet.insert(action02);
  actionSet.insert(action03);
  actionSet.insert(action04);

  using StateActionII = StateAction<AI::INT, AI::INT>;

  map<StateAction<AI::INT, AI::INT>, AI::FLOAT> stateActionPairValueMap;
  stateActionPairValueMap[StateActionII(dummyState, action01)] = 1.0F;
  stateActionPairValueMap[StateActionII(dummyState, action02)] = 2.0F;
  stateActionPairValueMap[StateActionII(dummyState, action03)] = -1.0F;
  stateActionPairValueMap[StateActionII(dummyState, action04)] = 2.2F;

  GIVEN("The following action-value map") {
    map<AI::INT, AI::FLOAT> actionValueMap;
    for (const AI::INT &action : actionSet) {
      actionValueMap[action] = stateActionPairValueMap.at(StateActionII(dummyState, action));
    }

    AI::UINT action01Ctr(0), action02Ctr(0), action03Ctr(0), action04Ctr(0);
    for (AI::INT i = 0; i < 1000; i++) {
      AI::INT action = policy.getAction(actionValueMap, actionSet);

      if (action == action01) {
        action01Ctr++;
      } else if (action == action02) {
        action02Ctr++;
      } else if (action == action03) {
        action03Ctr++;
      } else if (action == action04) {
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
