/*
 * GraphUndirected.h
 *
 *  Created on: Nov 12, 2014
 *      Author: jandres
 */

#ifndef INCLUDE_GRAPHUNDIRECTED_H_
#define INCLUDE_GRAPHUNDIRECTED_H_

#include <set>
#include <map>

#include "GraphDirected.h"

using namespace std;

namespace AI {
namespace Algorithm {
namespace Graph {

template<class D>
class GraphUndirected : public GraphDirected<D> {
 public:
  GraphUndirected(set<Edge<D> >& edgeSet);
  virtual ~GraphUndirected();

  virtual const set<const Vertex<D>*> getAdjacentLists(
      const Vertex<D>& v) const;
  virtual set<const Vertex<D>*> getAdjacentLists(const Vertex<D>& v);

  void rAddEdge(const Edge<D>& edge);
 protected:
  map<const Vertex<D>*, set<const Vertex<D>*> > _rAdjacencyLists;
};

template<class D>
GraphUndirected<D>::GraphUndirected(set<Edge<D> >& edgeSet)
    : GraphDirected<D>(edgeSet) {
  for (const Edge<D>& e : edgeSet) {
    rAddEdge(e);
  }
}

template<class D>
GraphUndirected<D>::~GraphUndirected() {
}

template<class D>
const set<const Vertex<D>*> GraphUndirected<D>::getAdjacentLists(
    const Vertex<D>& v) const {
  set<const Vertex<D>*> s = _rAdjacencyLists.at(&v);
  try {
    _rAdjacencyLists.at(&v);
  } catch (exception& except) {
    return s;
  }

  for (const Vertex<D>* n : _rAdjacencyLists.at(&v)) {
    s.insert(n);
  }
  return s;
}

template<class D>
set<const Vertex<D>*> GraphUndirected<D>::getAdjacentLists(const Vertex<D>& v) {
  set<const Vertex<D>*> s = _rAdjacencyLists[&v];
  try {
    _rAdjacencyLists[&v];
  } catch (exception& except) {
    return s;
  }

  for (const Vertex<D>* n : _rAdjacencyLists[&v]) {
    s.insert(n);
  }
  return s;
}

template<class D>
void GraphUndirected<D>::rAddEdge(const Edge<D>& edge) {
  _rAdjacencyLists.insert(
      std::pair<const Vertex<D>*, set<const Vertex<D>*> >(
          edge.getV2(), set<const Vertex<D>*>()));
  _rAdjacencyLists[edge.getV2()].insert(edge.getV1());
}

}  // namespace Graph
} /* namespace Algorithm */
} /* namespace AI */

#endif /* INCLUDE_GRAPHUNDIRECTED_H_ */
