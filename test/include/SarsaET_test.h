/**
 * SarsaET_test.h
 */

#pragma once

#include <cppunit/extensions/HelperMacros.h>

class SarsaET_test : public CppUnit::TestFixture{
  CPPUNIT_TEST_SUITE(SarsaET_test);
  CPPUNIT_TEST(episodeTest);
  CPPUNIT_TEST_SUITE_END();
 public:
  void episodeTest();
};
