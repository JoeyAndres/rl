/**
 * Sarsa_test.h
 */

#pragma once

#include <cppunit/extensions/HelperMacros.h>

class Sarsa_test : public CppUnit::TestFixture{
  CPPUNIT_TEST_SUITE(Sarsa_test);
  CPPUNIT_TEST(episodeTest);
  CPPUNIT_TEST_SUITE_END();
 public:
  void episodeTest();
};
