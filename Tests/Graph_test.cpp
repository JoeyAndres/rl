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
#include <set>
#include <iostream>

#include "UnitTest++.h"
#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include "DFS.h"

using namespace AI;
using namespace std;

TEST(VertexTest01) {
  Algorithm::Vertex<int> vertex01(10);
  CHECK((*vertex01.getData()) == 10);

  vertex01.setData(20);
  CHECK((*vertex01.getData()) == 20);
}

TEST(EdgeTest01) {
  Algorithm::Vertex<int> vertex01(10);
  Algorithm::Vertex<int> vertex02(20);
  Algorithm::Edge<int> edge01(vertex01, vertex02);

  CHECK((*(edge01.getV1()->getData())) == 10);
  CHECK((*(edge01.getV2()->getData())) == 20);
}

TEST(Graph01) {
  Algorithm::Vertex<int> vertex01(1);
  Algorithm::Vertex<int> vertex02(2);
  Algorithm::Vertex<int> vertex03(3);
  Algorithm::Vertex<int> vertex04(4);
  Algorithm::Vertex<int> vertex05(5);
  Algorithm::Vertex<int> vertex06(6);
  Algorithm::Vertex<int> vertex07(7);

 set<Algorithm::Edge<int> > edgeSet = {
    Algorithm::Edge<int> (vertex01, vertex02),
    Algorithm::Edge<int> (vertex01, vertex03),
    Algorithm::Edge<int> (vertex01, vertex04),
    Algorithm::Edge<int> (vertex02, vertex03),
    Algorithm::Edge<int> (vertex02, vertex05),
    Algorithm::Edge<int> (vertex03, vertex05),
    Algorithm::Edge<int> (vertex03, vertex01),
    Algorithm::Edge<int> (vertex02, vertex06),
    Algorithm::Edge<int> (vertex02, vertex07),
  };

  Algorithm::Graph<int> graph(edgeSet);

  /*for(const Algorithm::Vertex<int>* v : graph[vertex01]){
    cout << *(v->getData()) << endl;
  }*/

  for(const Algorithm::Vertex<int>* v  : graph.getVertices()){
    cout << *(v->getData()) << endl;
  }

  Algorithm::DFS<int> dfs(graph);
  dfs.search();
}

int main(void) {
  return UnitTest::RunAllTests();
}
