/**
 * StateAction_test.cpp
 */

#include "GlobalHeader.h"

#include <cppunit/TestAssert.h>

#include "StateAction_test.h"
#include "StateAction.h"

void StateAction_test::constructionTest(){
  AI::StateAction<AI::INT, AI::INT> stateAction(10, 10);
  CPPUNIT_ASSERT(stateAction.getState() == 10);
  CPPUNIT_ASSERT(stateAction.getAction() == 10);
}

void StateAction_test::accesorTest(){
  AI::StateAction<AI::INT, AI::INT> stateAction(10, 10);
  stateAction.setState(20);
  stateAction.setAction(20);
  CPPUNIT_ASSERT(stateAction.getState() != 10);
  CPPUNIT_ASSERT(stateAction.getAction() != 10);
  CPPUNIT_ASSERT(stateAction.getState() == 20);
  CPPUNIT_ASSERT(stateAction.getAction() == 20);
}

void StateAction_test::equalityOperatorTest(){
  AI::StateAction<AI::INT, AI::INT> stateAction01(10, 10);
  AI::StateAction<AI::INT, AI::INT> stateAction02(10, 10);
  CPPUNIT_ASSERT(stateAction01 == stateAction02);
}

void StateAction_test::lessThanOperatorTest(){
  AI::StateAction<AI::INT, AI::INT> stateAction01(10, 10);
  AI::StateAction<AI::INT, AI::INT> stateAction02(10, 20);

  CPPUNIT_ASSERT(stateAction01 != stateAction02);
  CPPUNIT_ASSERT(stateAction01 < stateAction02);

  AI::StateAction<AI::INT, AI::INT> stateAction03(10, 20);
  AI::StateAction<AI::INT, AI::INT> stateAction04(20, 10);
  CPPUNIT_ASSERT(stateAction03 != stateAction04);
  CPPUNIT_ASSERT(stateAction03 < stateAction04);
}



