/**
 * QLearningETWatkins_test.h
 */

#pragma once

#include <cppunit/extensions/HelperMacros.h>

class QLearningETWatkins_test : public CppUnit::TestFixture{
  CPPUNIT_TEST_SUITE(QLearningETWatkins_test);
  CPPUNIT_TEST(episodeTest);
  CPPUNIT_TEST_SUITE_END();
 public:
  void episodeTest();
};
