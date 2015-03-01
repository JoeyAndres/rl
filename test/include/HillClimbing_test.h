/**
 * HillClimbing_test.h
 */

#pragma once

#include <cppunit/extensions/HelperMacros.h>

class HillClimbing_test : public CppUnit::TestFixture{
  CPPUNIT_TEST_SUITE(HillClimbing_test);
  CPPUNIT_TEST(EightQueenSearchTest);
  CPPUNIT_TEST_SUITE_END();
 public:
  void EightQueenSearchTest();
};
