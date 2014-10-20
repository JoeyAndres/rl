/*
 * DFS.h
 *
 *  Created on: Oct 18, 2014
 *      Author: jandres
 */

#ifndef ALGORITHMS_GRAPH_DFS_H_
#define ALGORITHMS_GRAPH_DFS_H_

#include <map>
#include <set>

#include "Graph.h"

using namespace std;

namespace AI {
namespace Algorithm {

template<class D>
class DFS {
 public:
  DFS(Graph<D>& graph);
  virtual ~DFS();

  void search();
  virtual void traverse(Vertex<D>& startingVertex);
  virtual void previsit(Vertex<D>& startingVertex);
  virtual void postvisit(Vertex<D>& startingVertex);

  void reset();
 private:
  Graph<D>& _graph;
  map<Vertex<D>*, bool> _visited;
};

template<class D>
DFS<D>::DFS(Graph<D>& graph)
    : _graph(graph) {
  reset();
}

template<class D>
DFS<D>::~DFS() {
}

template<class D>
void DFS<D>::reset() {
  set<Vertex<D> > vertexSet = _graph.getVertices();
  for (Vertex<D> v : vertexSet) {
    _visited[v] = false;
  }
}

template<class D>
void DFS<D>::search() {
  reset();

  for(const Vertex<D  >& v : _graph.getVertices()){

  }
}

template<class D>
void DFS<D>::traverse(Vertex<D>& startingVertex) {
}

template<class D>
void DFS<D>::previsit(Vertex<D>& startingVertex) {
}

template<class D>
void DFS<D>::postvisit(Vertex<D>& startingVertex) {
}

}  // Algorithm.
}  // AI.

#endif /* ALGORITHMS_GRAPH_DFS_H_ */
