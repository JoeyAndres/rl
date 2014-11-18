/*
 * DFS.h
 *
 *  Created on: Oct 18, 2014
 *      Author: jandres
 */

#ifndef ALGORITHMS_GRAPH_DFS_H_
#define ALGORITHMS_GRAPH_DFS_H_

#include "GlobalHeader.h"

#include <map>
#include <set>

#include "GraphDirected.h"

using namespace std;

namespace AI {
namespace Algorithm {
namespace Graph {

template<class D>
class DFS {
 public:
  DFS(GraphDirected<D>& graph);
  virtual ~DFS();

  void search();
  virtual void traverse(const Vertex<D>* startingVertex);
  virtual void previsit(const Vertex<D>* vertex);
  virtual void postvisit(const Vertex<D>* vertex);

  /**
   * @param vertex
   * @return prenumber.
   */
  AI::UINT getPreNumber(const Vertex<D>* vertex) const;

  /**
   * @param vertex
   * @return postnumber.
   */
  AI::UINT getPostNumber(const Vertex<D>* vertex) const;

  void reset();

  /**
   * @return Corresponding graph.
   */
  const GraphDirected<D>& getGraph() const;
 private:
  GraphDirected<D>& _graph;
  map<const Vertex<D>*, bool> _visited;
  map<const Vertex<D>*, AI::UINT> _preNumber;
  map<const Vertex<D>*, AI::UINT> _postNumber;
  AI::UINT _ctr;
};

template<class D>
DFS<D>::DFS(GraphDirected<D>& graph)
    : _graph(graph) {
  _ctr = 0;
  reset();
}

template<class D>
DFS<D>::~DFS() {
}

template<class D>
void DFS<D>::reset() {
  _ctr = 0;
  set<const Vertex<D>*> vertexSet = _graph.getVertices();
  for (const Vertex<D>* v : vertexSet) {
    _visited[v] = false;
  }
  _preNumber.clear();
  _postNumber.clear();
}

template<class D>
void DFS<D>::search() {
  reset();

  for (const Vertex<D>* v : _graph.getVertices()) {
    if (_visited[v] == false) {
      traverse(v);
    }
  }
}

template<class D>
void DFS<D>::traverse(const Vertex<D>* startingVertex) {
  _visited[startingVertex] = true;

  previsit(startingVertex);
  for (const Vertex<D>* v : _graph.getAdjacentLists(*startingVertex)) {
    if (_visited[v] == false) {
      traverse(v);
    }
  }
  postvisit(startingVertex);
}

template<class D>
void DFS<D>::previsit(const Vertex<D>* vertex) {
  _preNumber[vertex] = _ctr++;
}

template<class D>
void DFS<D>::postvisit(const Vertex<D>* vertex) {
  _postNumber[vertex] = _ctr++  ;
}

template<class D>
AI::UINT DFS<D>::getPreNumber(const Vertex<D>* vertex) const{
  return _preNumber.at(vertex);
}

template<class D>
AI::UINT DFS<D>::getPostNumber(const Vertex<D>* vertex) const{
  return _postNumber.at(vertex);
}

template<class D>
const GraphDirected<D>& DFS<D>::getGraph() const{
  return _graph;
}

}  // namespace Graph
}  // namespace Algorithm.
}  // namespace AI.

#endif /* ALGORITHMS_GRAPH_DFS_H_ */
