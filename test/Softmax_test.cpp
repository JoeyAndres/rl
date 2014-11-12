#include <map>
#include <iostream>
#include <set>

#include "UnitTest++.h"
#include "Softmax.h"
#include "StateAction.h"
#include "StateAction.h"

using namespace AI;
using namespace AI::Algorithm;
using namespace std;

TEST(SoftmaxInitialization) {
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

  map<StateAction<AI::INT, AI::INT>, AI::FLOAT> stateActionPairValueMap;
  stateActionPairValueMap[StateAction<AI::INT, AI::INT>(dummyState, action01)] =
      1.0F;
  stateActionPairValueMap[StateAction<AI::INT, AI::INT>(dummyState, action02)] =
      2.0F;
  stateActionPairValueMap[StateAction<AI::INT, AI::INT>(dummyState, action03)] =
      -1.0F;
  stateActionPairValueMap[StateAction<AI::INT, AI::INT>(dummyState, action04)] =
      2.2F;

  map<AI::INT, AI::FLOAT> actionValueMap;
  for (const AI::INT& action : actionSet) {
    actionValueMap[action] = stateActionPairValueMap.at(
        StateAction<AI::INT, AI::INT>(dummyState, action));
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

  cout << "Action01 count " << action01Ctr << endl;
  cout << "Action02 count " << action02Ctr << endl;
  cout << "Action03 count " << action03Ctr << endl;
  cout << "Action04 count " << action04Ctr << endl;
  CHECK(action01Ctr > action03Ctr);
  CHECK(action02Ctr > action01Ctr);
  CHECK(action04Ctr > action02Ctr);
}

int main(void) {
  return UnitTest::RunAllTests();
}
