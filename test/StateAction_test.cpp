/*
 * StateAction_test.cpp
 *
 *  Created on: May 30, 2014
 *      Author: jandres
 */

#include "GlobalHeader.h"

#include "UnitTest++.h"

#include "StateAction.h"

TEST(StateActionInitialization) {
  AI::StateAction<AI::INT, AI::INT> stateAction(10, 10);
  CHECK(stateAction.getState() == 10);
  CHECK(stateAction.getAction() == 10);
}

TEST(StateActionAccessors) {
  AI::StateAction<AI::INT, AI::INT> stateAction(10, 10);
  stateAction.setState(20);
  stateAction.setAction(20);
  CHECK(stateAction.getState() != 10);
  CHECK(stateAction.getAction() != 10);
  CHECK(stateAction.getState() == 20);
  CHECK(stateAction.getAction() == 20);
}

TEST(StateActionEqualityOperator) {
  AI::StateAction<AI::INT, AI::INT> stateAction01(10, 10);
  AI::StateAction<AI::INT, AI::INT> stateAction02(10, 10);
  CHECK(stateAction01 == stateAction02);
}

TEST(StateActionLessOperator) {
  AI::StateAction<AI::INT, AI::INT> stateAction01(10, 10);
  AI::StateAction<AI::INT, AI::INT> stateAction02(10, 20);

  CHECK(stateAction01 != stateAction02);
  CHECK(stateAction01 < stateAction02);

  AI::StateAction<AI::INT, AI::INT> stateAction03(10, 20);
  AI::StateAction<AI::INT, AI::INT> stateAction04(20, 10);
  CHECK(stateAction03 != stateAction04);
  CHECK(stateAction03 < stateAction04);
}

int main(void) {
  return UnitTest::RunAllTests();
}
