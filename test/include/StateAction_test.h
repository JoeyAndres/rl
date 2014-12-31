/**
 * StateAction_test.h
 */

#pragma once

#include <cppunit/extensions/HelperMacros.h>

class StateAction_test : public CppUnit::TestFixture{
  CPPUNIT_TEST_SUITE(StateAction_test);
  CPPUNIT_TEST(constructionTest);
  CPPUNIT_TEST(accesorTest);
  CPPUNIT_TEST(equalityOperatorTest);
  CPPUNIT_TEST(lessThanOperatorTest);
  CPPUNIT_TEST_SUITE_END();
 public:
  void constructionTest();
  void accesorTest();
  void equalityOperatorTest();
  void lessThanOperatorTest();
};
