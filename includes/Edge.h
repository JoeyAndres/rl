/*
 * Edge.h
 *
 *  Created on: Oct 18, 2014
 *      Author: jandres
 */

#ifndef ALGORITHMS_GRAPH_EDGE_H_
#define ALGORITHMS_GRAPH_EDGE_H_

namespace AI {
namespace Algorithm {

template <class V>
class Edge {
 public:
  Edge(V v1, V v2);
  virtual ~Edge();

  const V* getV1() const;
  const V* getV2() const;

  void setV1(const V& v);
  void setV2(const V& v);

 private:
  V _v1; // Vertex 1.
  V _v2; // Vertex 2.
};

template <class V>
Edge<V>::Edge(V v1, V v2){
  _v1 = v1;
  _v2 = v2;
}

template <class V>
const V* Edge<V>::Edge::getV1() const{
  return &_v1;
}

template <class V>
const V* Edge<V>::Edge::getV2() const{
  return &_v2;
}


template <class V>
void Edge<V>::Edge::setV1(const V& v){
  _v1 = v;
}

template <class V>
void Edge<V>::Edge::setV2(const V& v){
  _v2 = v;
}

} /* namespace Algorithm */
} /* namespace AI */

#endif /* ALGORITHMS_GRAPH_EDGE_H_ */
