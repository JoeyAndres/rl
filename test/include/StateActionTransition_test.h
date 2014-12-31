/**
 * StateActionTransition_test.h
 */

#pragma once

#include <cppunit/extensions/HelperMacros.h>

class StateActionTransition_test : public CppUnit::TestFixture{
  CPPUNIT_TEST_SUITE(StateActionTransition_test);
  CPPUNIT_TEST(constructionTest);
  CPPUNIT_TEST(transitionUpdateTest);
  CPPUNIT_TEST(transitionExceptionCatchingTest);
  CPPUNIT_TEST_SUITE_END();
 public:
  void constructionTest();
  void transitionUpdateTest();
  void transitionExceptionCatchingTest();
};
