/*
 * Vertex.h
 *
 *  Created on: Oct 18, 2014
 *      Author: jandres
 */

#ifndef ALGORITHMS_GRAPH_VERTEX_H_
#define ALGORITHMS_GRAPH_VERTEX_H_

namespace AI {
namespace Algorithm {

template<class T>
class Vertex {
 public:
  Vertex(T data);
  virtual ~Vertex();

  const T* getData() const;
  void setData(T data);
 private:
  T _data;
};

template<class T>
Vertex<T>::Vertex(T data)
    : _data(data) {
}

template<class T>
Vertex<T>::~Vertex() {
}

template<class T>
const T* Vertex<T>::getData() const {
  return &_data;
}

template<class T>
void Vertex<T>::setData(T data) {
  _data = data;
}

} /* namespace Algorithm */
} /* namespace AI */

#endif /* ALGORITHMS_GRAPH_VERTEX_H_ */
