/*
 * Graph_test.cpp
 */

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <cppunit/TestAssert.h>

#include "Graph_test.h"
#include "Vertex.h"
#include "Edge.h"
#include "GraphDirected.h"
#include "GraphUndirected.h"
#include "DFS.h"
#include "BFS.h"
#include "Linearize.h"

using namespace AI;
using namespace std;

void Graph_test::vertexTest(){
  Algorithm::Graph::Vertex<int> vertex01(10);
  CPPUNIT_ASSERT_EQUAL((*vertex01.getData()), 10);

  vertex01.setData(20);
  CPPUNIT_ASSERT_EQUAL((*vertex01.getData()), 20);
}

void Graph_test::edgeTest(){
  Algorithm::Graph::Vertex<int> vertex01(10);
  Algorithm::Graph::Vertex<int> vertex02(20);
  Algorithm::Graph::Edge<int> edge01(vertex01, vertex02);

  CPPUNIT_ASSERT_EQUAL((*(edge01.getV1()->getData())), 10);
  CPPUNIT_ASSERT_EQUAL((*(edge01.getV2()->getData())), 20);
}

void Graph_test::graphTest(){
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
    CPPUNIT_ASSERT(vertexSet.find(*v) != vertexSet.end());
  }

  Algorithm::Graph::BFS<int> bfs;
  bfs.search(graph, vertex01);

  Algorithm::Graph::BFS<int> dBfs;
  dBfs.search(dGraph, vertex01);

  Algorithm::Graph::DFS<int> dfs;
  dfs.search(graph);
  map<const AI::Algorithm::Graph::Vertex<int>*, AI::UINT> preNumber;
  map<const AI::Algorithm::Graph::Vertex<int>*, AI::UINT> postNumber;
  dfs.search(graph, vertex02, preNumber, postNumber);

  for(auto  p : postNumber){
    cout << *(p.first->getData()) << ": " << p.second << ", ";
  }
  cout << endl;

  dfs.search(dGraph);
  
  Algorithm::Graph::Linearize<int> lin;
  lin.linearize(graph);
}
