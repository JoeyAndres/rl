/**
 * DynaQPrioritizeSweeping_test.cpp
 */

#pragma once

#include <cppunit/extensions/HelperMacros.h>

class DynaQPrioritizedSweeping_test : public CppUnit::TestFixture{
  CPPUNIT_TEST_SUITE(DynaQPrioritizedSweeping_test);
  CPPUNIT_TEST(episodeTest);
  CPPUNIT_TEST_SUITE_END();
 public:
  void episodeTest();
};
