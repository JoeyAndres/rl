/**
 * DynaQ_test.h
 */

#pragma once

#include <cppunit/extensions/HelperMacros.h>

class DynaQ_test : public CppUnit::TestFixture{
  CPPUNIT_TEST_SUITE(DynaQ_test);
  CPPUNIT_TEST(episodeTest);
  CPPUNIT_TEST_SUITE_END();
 public:
  void episodeTest();
};
