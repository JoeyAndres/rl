/*
 * Graph_test.cpp
 *
 *  Created on: Oct 18, 2014
 *      Author: jandres
 */

#include <vector>
#include <set>
#include <iostream>

#include "UnitTest++.h"
#include "Vertex.h"
#include "Edge.h"
#include "GraphDirected.h"
#include "GraphUndirected.h"
#include "DFS.h"
#include "BFS.h"
#include "Linearize.h"

using namespace AI;
using namespace std;

TEST(VertexTest01) {
  Algorithm::Graph::Vertex<int> vertex01(10);
  CHECK((*vertex01.getData()) == 10);

  vertex01.setData(20);
  CHECK((*vertex01.getData()) == 20);
}

TEST(EdgeTest01) {
  Algorithm::Graph::Vertex<int> vertex01(10);
  Algorithm::Graph::Vertex<int> vertex02(20);
  Algorithm::Graph::Edge<int> edge01(vertex01, vertex02);

  CHECK((*(edge01.getV1()->getData())) == 10);
  CHECK((*(edge01.getV2()->getData())) == 20);
}

TEST(Graph01) {
  Algorithm::Graph::Vertex<int> vertex01(1);
  Algorithm::Graph::Vertex<int> vertex02(2);
  Algorithm::Graph::Vertex<int> vertex03(3);
  Algorithm::Graph::Vertex<int> vertex04(4);
  Algorithm::Graph::Vertex<int> vertex05(5);
  Algorithm::Graph::Vertex<int> vertex06(6);
  Algorithm::Graph::Vertex<int> vertex07(7);

  set<Algorithm::Graph::Vertex<int> > vertexSet = { 
    vertex01, 
    vertex02,
    vertex03, 
    vertex04, 
    vertex05, 
    vertex06, 
    vertex07, 
    vertex07 
  };

  set<Algorithm::Graph::Edge<int> > edgeSet = { 
    Algorithm::Graph::Edge<int>(vertex01, vertex02), 
    Algorithm::Graph::Edge<int>(vertex01, vertex03),
    Algorithm::Graph::Edge<int>(vertex01, vertex04), 
    Algorithm::Graph::Edge<int>(vertex02, vertex03), 
    Algorithm::Graph::Edge<int>(vertex02, vertex05),
    Algorithm::Graph::Edge<int>(vertex03, vertex05), 
    Algorithm::Graph::Edge<int>(vertex03, vertex01),
    Algorithm::Graph::Edge<int>(vertex02, vertex06),
    Algorithm::Graph::Edge<int>(vertex02, vertex07), 
  };

  Algorithm::Graph::GraphDirected<int> dGraph(edgeSet);
  Algorithm::Graph::GraphUndirected<int> graph(edgeSet);

  for (const Algorithm::Graph::Vertex<int>* v : graph.getVertices()) {
    CHECK(vertexSet.find(*v) != vertexSet.end());
  }

  cout << "Directed Graph BFS" << endl;
  Algorithm::Graph::BFS<int> bfs(graph);
  bfs.search(vertex01);

  //cout << "Undirected Graph BFS" << endl;
  //Algorithm::Graph::BFS<int> dBfs(dGraph);
  //dBfs.search(vertex01);

  cout << "Undirected Graph DFS" << endl;
  Algorithm::Graph::DFS<int> dfs;
  dfs.search(graph, NULL, NULL);

  cout << "Directed Graph DFS" << endl;
  dfs.search(dGraph, NULL, NULL);

  //cout << "Linearize DGraph DFS" << endl;
  //Algorithm::Graph::Linearize<int> lin(dGraph);
  //lin.linearize();
}

int main(void) {
  return UnitTest::RunAllTests();
}
