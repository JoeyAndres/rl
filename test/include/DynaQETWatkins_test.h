/**
 * DynaQETWatkins_test.cpp
 */

#pragma once

#include <cppunit/extensions/HelperMacros.h>

class DynaQETWatkins_test : public CppUnit::TestFixture{
  CPPUNIT_TEST_SUITE(DynaQETWatkins_test);
  CPPUNIT_TEST(episodeTest);
  CPPUNIT_TEST_SUITE_END();
public:
  void episodeTest();
};

