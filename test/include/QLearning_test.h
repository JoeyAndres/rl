/**
 * QLearning_test.h
 */

#pragma once

#include <cppunit/extensions/HelperMacros.h>

class QLearning_test : public CppUnit::TestFixture{
  CPPUNIT_TEST_SUITE(QLearning_test);
  CPPUNIT_TEST(episodeTest);
  CPPUNIT_TEST_SUITE_END();
 public:
  void episodeTest();
};
