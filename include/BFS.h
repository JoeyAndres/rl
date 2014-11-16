/*
 * BFS.h
 *
 *  Created on: Nov 15, 2014
 *      Author: jandres
 */

#ifndef INCLUDE_BFS_H_
#define INCLUDE_BFS_H_

#include <map>
#include <set>
#include <queue>

#include "GraphDirected.h"

using namespace std;

namespace AI {
namespace Algorithm {
namespace Graph {

template<class D>
class BFS {
 public:
  BFS(GraphDirected<D>& graph);
  virtual ~BFS();

  void search(const Vertex<D>& vertex);

  void reset();

  void visit(const Vertex<D>& vertex);
 private:
  GraphDirected<D>& _graph;
  queue<const Vertex<D>*> _queue;
  map<const Vertex<D>*, bool> _visited;
};

template<class D>
BFS<D>::BFS(GraphDirected<D>& graph)
    : _graph(graph) {
  reset();
}

template<class D>
BFS<D>::~BFS() {
}

template<class D>
void BFS<D>::reset() {
  set<const Vertex<D>*> vertexSet = _graph.getVertices();
  for (const Vertex<D>* v : vertexSet) {
    _visited[v] = false;
  }
}

template<class D>
void BFS<D>::search(const Vertex<D>& vertex) {
  reset();
  _queue.push(&vertex);

  while(_queue.empty() == false){
    const Vertex<D>* v = _queue.front();
    _queue.pop();
    _visited[v] = true;
    for (const Vertex<D>* neighbour : _graph.getAdjacentLists(*v)) {
      if(_visited[neighbour] == false){
        visit(*neighbour);
        _queue.push(neighbour);
      }
    }
  }
}

template<class D>
void BFS<D>::visit(const Vertex<D>& vertex){
  // Override.
}

} /* namespace Graph */
} /* namespace Algorithm */
} /* namespace AI */

#endif /* INCLUDE_BFS_H_ */
