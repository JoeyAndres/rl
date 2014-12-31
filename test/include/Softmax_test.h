/**
 * Softmax_test.h
 */

#pragma once

#include <cppunit/extensions/HelperMacros.h>

class Softmax_test : public CppUnit::TestFixture{
  CPPUNIT_TEST_SUITE(Softmax_test);
  CPPUNIT_TEST(episodeTest);
  CPPUNIT_TEST_SUITE_END();
 public:
  void episodeTest();
};
