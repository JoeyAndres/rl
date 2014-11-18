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
  BFS();
  virtual ~BFS();
  void search(GraphDirected<D>& graph, const Vertex<D>& vertex);  
  void visit(const Vertex<D>& vertex);
};

template<class D>
BFS<D>::BFS(){
}

template<class D>
BFS<D>::~BFS() {
}

template<class D>    
void BFS<D>::search(GraphDirected<D>& graph, const Vertex<D>& startingVertex){
  queue<const Vertex<D>*> q;
  map<const Vertex<D>*, bool> visited;

  // Initialize visited.
  for(const Vertex<D>* v : graph.getVertices()){
    visited[v] = false;
  }
  
  q.push(&startingVertex);

  while(q.empty() == false){
    const Vertex<D>* v = q.front();
    q.pop();
    visited[v] = true;
    for (const Vertex<D>* neighbour : graph.getAdjacentLists(*v)) {
      if(visited[neighbour] == false){
        visit(*neighbour);
        q.push (neighbour);
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
