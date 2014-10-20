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

  const set<Vertex<D> >& operator[](const Vertex<D>& v) const;
  const set<Vertex<D> >& getAdjacentLists(const Vertex<D>& v) const;

  set<Vertex<D> >& operator[](const Vertex<D>& v);
  set<Vertex<D> >& getAdjacentLists(const Vertex<D>& v);

  const set<Vertex<D> > getVertices() const;
  set<Vertex<D> > getVertices();
 private:
  map<Vertex<D>, set<Vertex<D> > > _adjacencyLists;
};

template<class D>
Graph<D>::Graph(set<Edge<D> > edgeSet) {
  for (const Edge<D>& e : edgeSet) {
    _adjacencyLists.insert(
        std::pair<Vertex<D>, set<Vertex<D> > >((*e.getV1()),
                                               set<Vertex<D> >()));
    set<Vertex<D> >& list = this->_adjacencyLists[(*e.getV1())];
    list.insert((*e.getV2()));
  }
}

template<class D>
Graph<D>::~Graph() {
}

template<class D>
const set<Vertex<D> >& Graph<D>::operator[](const Vertex<D>& v) const {
  return _adjacencyLists[v];
}

template<class D>
const set<Vertex<D> >& Graph<D>::getAdjacentLists(const Vertex<D>& v) const {
  return _adjacencyLists[v];
}

template<class D>
set<Vertex<D> >& Graph<D>::operator[](const Vertex<D>& v) {
  return _adjacencyLists[v];
}

template<class D>
set<Vertex<D> >& Graph<D>::getAdjacentLists(const Vertex<D>& v) {
  return _adjacencyLists[v];
}

template<class D>
const set<Vertex<D> > Graph<D>::getVertices() const {
  set<Vertex<D> > vertices;
  for (const std::pair<Vertex<D>, set<Vertex<D> > >& pair : _adjacencyLists) {
    vertices.insert(pair.first);
    for (const Vertex<D>& v : pair.second) {
      vertices.insert(v);
    }
  }

  return vertices;
}

template<class D>
set<Vertex<D> > Graph<D>::getVertices(){
  set<Vertex<D> > vertices;
  for (const std::pair<Vertex<D>, set<Vertex<D> > >& pair : _adjacencyLists) {
    vertices.insert(pair.first);
    for (const Vertex<D>& v : pair.second) {
      vertices.insert(v);
    }
  }

  return vertices;
}

} /* namespace Algorithm */
} /* namespace AI */

#endif /* ALGORITHMS_GRAPH_GRAPH_H_ */
