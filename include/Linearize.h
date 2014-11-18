/*
 * Linearize.h
 *
 *  Created on: Nov 16, 2014
 *      Author: jandres
 */

#ifndef INCLUDE_LINEARIZE_H_
#define INCLUDE_LINEARIZE_H_

#include "DFS.h"
#include "GraphDirected.h"
#include "Vertex.h"

using namespace std;

namespace AI {
namespace Algorithm {
namespace Graph {

template<class D>
class Linearize {
 public:
  Linearize();
  virtual ~Linearize();

  vector<const Vertex<D>*> linearize(GraphDirected<D>& graph, Vertex<D>& startingVertex) const;
  vector<const Vertex<D>*> linearize(GraphDirected<D>& graph) const;

 protected:
  DFS<D> _dfs;
};

template<class D>
Linearize<D>::Linearize(){
}

template<class D>
Linearize<D>::~Linearize() {
}

template<class D>
vector<const Vertex<D>*> Linearize<D>::linearize(GraphDirected<D>& graph) const{
  map<const Vertex<D>*, AI::UINT> pre;
  map<const Vertex<D>*, AI::UINT> post;
  _dfs.search(graph, pre, post);

  vector<const Vertex<D>*> linearOrderVertices;
  for(const Vertex<D>* v : graph.getVertices()){
    linearOrderVertices.push_back(v);
  }

  return linearOrderVertices;
}

template<class D>
vector<const Vertex<D>*> Linearize<D>::linearize(GraphDirected<D>& graph, Vertex<D>& startingVertex) const{
  map<const Vertex<D>*, AI::UINT> pre;
  map<const Vertex<D>*, AI::UINT> post;
  _dfs.search(graph, startingVertex, pre, post);

  vector<const Vertex<D>*> linearOrderVertices;
  for(const Vertex<D>* v : graph.getVertices()){
    linearOrderVertices.push_back(v);
  }

  return linearOrderVertices;
}


} /* namespace Graph */
} /* namespace Algorithm */
} /* namespace AI */

#endif /* INCLUDE_LINEARIZE_H_ */
