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

template<class D>
class GraphUndirected : public GraphDirected {
 public:
  GraphUndirected(set<Edge<D> > edgeSet);

 protected:
  map<const Vertex<D>*, set<const Vertex<D>*> > _rAdjacencyLists;
};

template<class D>
GraphUndirected<D>::GraphUndirected(set<Edge<D> > edgeSet)
    : GraphDirected<D>(set < Edge<D> > edgeSet) {
  for
}

} /* namespace Algorithm */
} /* namespace AI */

#endif /* INCLUDE_GRAPHUNDIRECTED_H_ */
