/*
 * Edge.h
 *
 *  Created on: Oct 18, 2014
 *      Author: jandres
 */

#ifndef ALGORITHMS_GRAPH_EDGE_H_
#define ALGORITHMS_GRAPH_EDGE_H_

#include "Vertex.h"

namespace AI {
namespace Algorithm {

template<class V>
class Edge {
 public:
  Edge(Vertex<V> v1, Vertex<V> v2);
  virtual ~Edge();

  const Vertex<V>* getV1() const;
  const Vertex<V>* getV2() const;

  void setV1(const Vertex<V>& v);
  void setV2(const Vertex<V>& v);

  bool operator<(const Edge<V>& vertex) const;

 private:
  Vertex<V> _v1;  //!< Vertex 1.
  Vertex<V> _v2;  //!< Vertex 2.
};

template<class V>
Edge<V>::Edge(Vertex<V> v1, Vertex<V> v2)
    : _v1(v1),
      _v2(v2) {
}

template<class V>
Edge<V>::~Edge() {
}

template<class V>
const Vertex<V>* Edge<V>::Edge::getV1() const {
  return &_v1;
}

template<class V>
const Vertex<V>* Edge<V>::Edge::getV2() const {
  return &_v2;
}

template<class V>
void Edge<V>::Edge::setV1(const Vertex<V>& v) {
  _v1 = v;
}

template<class V>
void Edge<V>::Edge::setV2(const Vertex<V>& v) {
  _v2 = v;
}

template<class V>
bool Edge<V>::operator<(const Edge<V>& vertex) const{
  if(_v1 < vertex._v1){
    return true;
  }else if(_v1 > vertex._v1){
    return false;
  }

  if(_v2 < vertex._v2){
    return true;
  }else{
    return false;
  }
}

} /* namespace Algorithm */
} /* namespace AI */

#endif /* ALGORITHMS_GRAPH_EDGE_H_ */
