/**
 * TileCode_test.h
 */

#pragma once

#include <cppunit/extensions/HelperMacros.h>

class TileCode_test : public CppUnit::TestFixture{
  CPPUNIT_TEST_SUITE(TileCode_test);
  CPPUNIT_TEST(basicTest);
  CPPUNIT_TEST_SUITE_END();
 public:
  void basicTest();
};
