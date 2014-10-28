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
class Graph {
 public:
  Graph(set<Edge<D> > edgeSet);
  virtual ~Graph();

  const set<const Vertex<D>*> operator[](const Vertex<D>& v) const;
  const set<const Vertex<D>*> getAdjacentLists(const Vertex<D>& v) const;

  set<const Vertex<D>*> operator[](const Vertex<D>& v);
  set<const Vertex<D>*> getAdjacentLists(const Vertex<D>& v);

  const set<const Vertex<D>*> getVertices() const;
  set<const Vertex<D>*> getVertices();
 private:
  map<const Vertex<D>*, set<const Vertex<D>*> > _adjacencyLists;
};

template<class D>
Graph<D>::Graph(set<Edge<D> > edgeSet) {
  for (const Edge<D>& e : edgeSet) {
    _adjacencyLists.insert(
        std::pair<const Vertex<D>*, set<const Vertex<D>*> >(
            e.getV1(), set<const Vertex<D>*>()));
    set<const Vertex<D>*>& list01 = this->_adjacencyLists[e.getV1()];
    list01.insert(e.getV2());

    _adjacencyLists.insert(
        std::pair<const Vertex<D>*, set<const Vertex<D>*> >(
            e.getV2(), set<const Vertex<D>*>()));
    set<const Vertex<D>*>& list02 = this->_adjacencyLists[e.getV2()];
    list02.insert(e.getV1());
  }
}

template<class D>
Graph<D>::~Graph() {
}

template<class D>
const set<const Vertex<D>*> Graph<D>::operator[](const Vertex<D>& v) const {
  try {
    _adjacencyLists[&v];
  } catch (exception& except) {
    return set<const Vertex<D>*>();
  }
  return _adjacencyLists[&v];
}

template<class D>
const set<const Vertex<D>*> Graph<D>::getAdjacentLists(
    const Vertex<D>& v) const {
  try {
    _adjacencyLists[&v];
  } catch (exception& except) {
    return set<const Vertex<D>*>();
  }
  return _adjacencyLists[&v];
}

template<class D>
set<const Vertex<D>*> Graph<D>::operator[](const Vertex<D>& v) {
  try {
    _adjacencyLists[&v];
  } catch (exception& except) {
    return set<const Vertex<D>*>();
  }
  return _adjacencyLists[&v];
}

template<class D>
set<const Vertex<D>*> Graph<D>::getAdjacentLists(const Vertex<D>& v) {
  try {
    _adjacencyLists[&v];
  } catch (exception& except) {
    return set<const Vertex<D>*>();
  }
  return _adjacencyLists[&v];
}

template<class D>
const set<const Vertex<D>*> Graph<D>::getVertices() const {
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
set<const Vertex<D>*> Graph<D>::getVertices() {
  set<const Vertex<D>*> vertices;
  for (const std::pair<const Vertex<D>*, set<const Vertex<D>*> >& pair : _adjacencyLists) {
    vertices.insert(pair.first);
    for (const Vertex<D>* v : pair.second) {
      vertices.insert(v);
    }
  }

  return vertices;
}

} /* namespace Algorithm */
} /* namespace AI */

#endif /* ALGORITHMS_GRAPH_GRAPH_H_ */
