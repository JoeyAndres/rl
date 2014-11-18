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
  Linearize(GraphDirected<D>& graph);
  virtual ~Linearize();

  void linearize();

 protected:
  vector<const Vertex<D>*> _linearOrdered;
  DFS<D> _dfs;
};

template<class D>
Linearize<D>::Linearize(GraphDirected<D>& graph)
    : _dfs(graph) {
}

template<class D>
Linearize<D>::~Linearize() {
}

template<class D>
void Linearize<D>::linearize() {
  _dfs.search();

  const GraphDirected<D>& g = _dfs.getGraph();
  const set<const Vertex<D>*> vertices = g.getVertices();

  map<AI::UINT, const Vertex<D>*> reversePostOrderMap;
  for(const Vertex<D>* pV : vertices){
    reversePostOrderMap[_dfs.getPostNumber(pV)] = pV;
  }

  for(typename map<AI::UINT, const Vertex<D>*>::const_iterator iter = reversePostOrderMap.begin();
      iter != reversePostOrderMap.end(); iter++){
    _linearOrdered.push_back(iter->second);
  }
}

} /* namespace Graph */
} /* namespace Algorithm */
} /* namespace AI */

#endif /* INCLUDE_LINEARIZE_H_ */
