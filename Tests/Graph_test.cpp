/*
 * Graph_test.cpp
 *
 *  Created on: Oct 18, 2014
 *      Author: jandres
 */

/*
 * Sarsa_test.cpp
 *
 *  Created on: May 31, 2014
 *      Author: jandres
 */

#include <vector>
#include <iostream>

#include "UnitTest++.h"
#include "Vertex.h"
#include "Edge.h"

using std::vector;

using namespace AI;
using namespace std;

TEST(VertexTest01) {
  Algorithm::Vertex<int> vertex01(10);
  CHECK((*vertex01.getData()) == 10);

  vertex01.setData(20);
  CHECK((*vertex01.getData()) == 20);
}

TEST(EdgeTest01) {
  Algorithm::Edge<int> vertex01(10, 20);
}

int main(void) {
  return UnitTest::RunAllTests();
}
