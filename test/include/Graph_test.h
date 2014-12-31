/**
 * Graph_test.h
 */

#pragma once

#include <cppunit/extensions/HelperMacros.h>

class Graph_test : public CppUnit::TestFixture{
  CPPUNIT_TEST_SUITE(Graph_test);
  CPPUNIT_TEST(vertexTest);
  CPPUNIT_TEST(edgeTest);
  CPPUNIT_TEST(graphTest);
  CPPUNIT_TEST_SUITE_END();
 public:
  void vertexTest();
  void edgeTest();
  void graphTest();
};
