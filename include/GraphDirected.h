/*
 * Graph.h
 *
 *  Created on: Oct 18, 2014
 *      Author: jandres
 */

#ifndef ALGORITHMS_GRAPH_GRAPH_H_
#define ALGORITHMS_GRAPH_GRAPH_H_

#include <map>
#include <set>

#include "Edge.h"
#include "Vertex.h"

using namespace std;

namespace AI {
namespace Algorithm {

template<class D>
class GraphDirected {
 public:
  GraphDirected(set<Edge<D> >& edgeSet);
  virtual ~GraphDirected();

  const set<const Vertex<D>*> operator[](const Vertex<D>& v) const;
  const set<const Vertex<D>*> getAdjacentLists(const Vertex<D>& v) const;

  set<const Vertex<D>*> operator[](const Vertex<D>& v);
  set<const Vertex<D>*> getAdjacentLists(const Vertex<D>& v);

  const set<const Vertex<D>*> getVertices() const;
  set<const Vertex<D>*> getVertices();

  void addEdge(const Edge<D>& edge);

 protected:
  map<const Vertex<D>*, set<const Vertex<D>*> > _adjacencyLists;
};

template<class D>
GraphDirected<D>::GraphDirected(set<Edge<D> >& edgeSet) {
  // Add vertices.
  for (const Edge<D>& e : edgeSet) {
    // Add e[0] -> (e[0], v), v in V.
    addEdge(e);

    // Add e[1] -> (e[1], v), v in V.
    Vertex<D> v1 = *(e.getV2());
    Vertex<D> v2 = *(e.getV1());

    addEdge(Edge<D>(v1, v2));
  }
}

template<class D>
GraphDirected<D>::~GraphDirected() {
}

template<class D>
const set<const Vertex<D>*> GraphDirected<D>::operator[](
    const Vertex<D>& v) const {
  try {
    _adjacencyLists[&v];
  } catch (exception& except) {
    return set<const Vertex<D>*>();
  }
  return _adjacencyLists[&v];
}

template<class D>
const set<const Vertex<D>*> GraphDirected<D>::getAdjacentLists(
    const Vertex<D>& v) const {
  try {
    _adjacencyLists[&v];
  } catch (exception& except) {
    return set<const Vertex<D>*>();
  }
  return _adjacencyLists[&v];
}

template<class D>
set<const Vertex<D>*> GraphDirected<D>::operator[](const Vertex<D>& v) {
  try {
    _adjacencyLists[&v];
  } catch (exception& except) {
    return set<const Vertex<D>*>();
  }
  return _adjacencyLists[&v];
}

template<class D>
set<const Vertex<D>*> GraphDirected<D>::getAdjacentLists(const Vertex<D>& v) {
  try {
    _adjacencyLists[&v];
  } catch (exception& except) {
    return set<const Vertex<D>*>();
  }
  return _adjacencyLists[&v];
}

template<class D>
const set<const Vertex<D>*> GraphDirected<D>::getVertices() const {
  set<const Vertex<D>*> vertices;
  for (const std::pair<const Vertex<D>*, set<const Vertex<D>*> >& pair : _adjacencyLists) {
    vertices.insert(pair.first);
    for (const Vertex<D>* v : pair.second) {
      vertices.insert(v);
    }
  }

  return vertices;
}

template<class D>
set<const Vertex<D>*> GraphDirected<D>::getVertices() {
  set<const Vertex<D>*> vertices;
  for (const std::pair<const Vertex<D>*, set<const Vertex<D>*> >& pair : _adjacencyLists) {
    vertices.insert(pair.first);
    for (const Vertex<D>* v : pair.second) {
      vertices.insert(v);
    }
  }

  return vertices;
}

template<class D>
void GraphDirected<D>::addEdge(const Edge<D>& edge) {
  _adjacencyLists.insert(
      std::pair<const Vertex<D>*, set<const Vertex<D>*> >(
          edge.getV1(), set<const Vertex<D>*>()));
  _adjacencyLists[edge.getV1()].insert(edge.getV2());
}

} /* namespace Algorithm */
} /* namespace AI */

#endif /* ALGORITHMS_GRAPH_GRAPH_H_ */