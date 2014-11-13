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

#include "GraphDirected.h"

using namespace std;

namespace AI {
namespace Algorithm {

template<class D>
class DFS {
 public:
  DFS(GraphDirected<D>& graph);
  virtual ~DFS();

  void search();
  virtual void traverse(const Vertex<D>* startingVertex);
  virtual void previsit(const Vertex<D>* startingVertex);
  virtual void postvisit(const Vertex<D>* startingVertex);

  void reset();
 private:
  GraphDirected<D>& _graph;
  map<const Vertex<D>*, bool> _visited;
};

template<class D>
DFS<D>::DFS(GraphDirected<D>& graph)
    : _graph(graph) {
  reset();
}

template<class D>
DFS<D>::~DFS() {
}

template<class D>
void DFS<D>::reset() {
  set<const Vertex<D>*> vertexSet = _graph.getVertices();
  for (const Vertex<D>* v : vertexSet) {
    _visited[v] = false;
  }
}

template<class D>
void DFS<D>::search() {
  reset();

  for (const Vertex<D>* v : _graph.getVertices()) {
    if (_visited[v] == false) {
      traverse(v);
    }
  }
}

template<class D>
void DFS<D>::traverse(const Vertex<D>* startingVertex) {
  _visited[startingVertex] = true;

  previsit(startingVertex);
  for (const Vertex<D>* v : _graph.getAdjacentLists(*startingVertex)) {
    if (_visited[v] == false) {
      traverse(v);
    }
  }
  postvisit(startingVertex);
}

template<class D>
void DFS<D>::previsit(const Vertex<D>* startingVertex) {
  cout << "Pre: " << *(startingVertex->getData()) << endl;
}

template<class D>
void DFS<D>::postvisit(const Vertex<D>* startingVertex) {
  cout << "Post: " << *(startingVertex->getData()) << endl;
}

}  // Algorithm.
}  // AI.

#endif /* ALGORITHMS_GRAPH_DFS_H_ */
