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
#include <stack>

#include "GraphDirected.h"

using namespace std;

namespace AI {
namespace Algorithm {
namespace Graph {

template<class D>
class DFS {
 public:
  DFS();
  virtual ~DFS();

  void search(GraphDirected<D>& graph,
              map<const Vertex<D>*, AI::UINT>& preNumber, 
              map<const Vertex<D>*, AI::UINT>& postNumber) const;

  void search(GraphDirected<D>& graph) const;
  
  void search(GraphDirected<D>& graph,
              const Vertex<D>& startingVertex,
              map<const Vertex<D>*, AI::UINT>& preNumber, 
              map<const Vertex<D>*, AI::UINT>& postNumber) const;

  void search(GraphDirected<D>& graph, const Vertex<D>& startingVertex) const;
  
  virtual void traverse(const GraphDirected<D>& graph,
                        map<const Vertex<D>*, bool>& visited,
                        const Vertex<D>& startingVertex,
                        AI::UINT& ctr,
                        map<const Vertex<D>*, AI::UINT>& preNumber, 
                        map<const Vertex<D>*, AI::UINT>& postNumber) const;
  
  virtual void traverse(const GraphDirected<D>& graph,
                        map<const Vertex<D>*, bool>& visited,
                        const Vertex<D>& startingVertex) const;
 
  virtual void previsit(const GraphDirected<D>& graph, 
                        map<const Vertex<D>*, bool>& visited,
                        const Vertex<D>& vertex,
                        AI::UINT& ctr,
                        map<const Vertex<D>*, AI::UINT>& preNumber,
                        map<const Vertex<D>*, AI::UINT>& postNumber) const;
  virtual void postvisit(const GraphDirected<D>& graph,
                         map<const Vertex<D>*, bool>& visited,
                         const Vertex<D>& vertex,
                         AI::UINT& ctr,
                         map<const Vertex<D>*, AI::UINT>& preNumber,
                         map<const Vertex<D>*, AI::UINT>& postNumber) const;
  virtual void visit(const Vertex<D>* vertex);

 private:
  void _initializeVisited(const GraphDirected<D>& graph,
                          map<const Vertex<D> *, bool>& visited) const;

  void _traverseAllVertices(const GraphDirected<D>& graph,
                            map<const Vertex<D> *, bool>& visited) const;
  void _traverseAllVertices(const GraphDirected<D>& graph,
                            map<const Vertex<D> *, bool>& visited,
                            AI::UINT& ctr,
                            map<const Vertex<D>*, AI::UINT>& preNumber,
                            map<const Vertex<D>*, AI::UINT>& postNumber) const;                            
};

template<class D>
DFS<D>::DFS(){}

template<class D>
DFS<D>::~DFS() {}

template<class D>
void DFS<D>::search(GraphDirected<D>& graph,
                    map<const Vertex<D>*, AI::UINT>& preNumber,
                    map<const Vertex<D>*, AI::UINT>& postNumber) const{
  // Initialize visited map.
  map<const Vertex<D>*, bool> visited;
  _initializeVisited(graph, visited);
  
  // Try traversing to each vertex.
  AI::UINT ctr = 0;
  _traverseAllVertices(graph, visited, ctr, preNumber, postNumber);
}

template<class D>
void DFS<D>::search(GraphDirected<D>& graph) const{
  // Initialize visited map.
  map<const Vertex<D>*, bool> visited;
  _initializeVisited(graph, visited);
	
  // Try traversing to each vertex.
  _traverseAllVertices(graph, visited);
}

template<class D>
void DFS<D>::search(GraphDirected<D>& graph,
                    const Vertex<D>& startingVertex,
                    map<const Vertex<D>*, AI::UINT>& preNumber,
                    map<const Vertex<D>*, AI::UINT>& postNumber) const{
  // Initialize visited map.
  map<const Vertex<D>*, bool> visited;
  _initializeVisited(graph, visited);

  AI::UINT ctr = 0;

  // Traverse startingVertex.
  traverse(graph, visited, startingVertex, ctr, preNumber, postNumber);
	
  // Try traversing to each vertex.
  _traverseAllVertices(graph, visited, ctr, preNumber, postNumber);
}

template<class D>
void DFS<D>::search(GraphDirected<D>& graph, const Vertex<D>& startingVertex) const{
  // Initialize visited map.
  map<const Vertex<D>*, bool> visited;
  _initializeVisited(visited, graph);

  // Traverse startingVertex.
  traverse(graph, visited, startingVertex);
	
  // Try traversing to each vertex.
  _traverseAllVertices(graph, visited);
}
      
template<class D>
void DFS<D>::traverse(const GraphDirected<D>& graph,
                      map<const Vertex<D>*, bool>& visited,
                      const Vertex<D>& startingVertex,
                      AI::UINT& ctr,
                      map<const Vertex<D>*, AI::UINT>& preNumber,
                      map<const Vertex<D>*, AI::UINT>& postNumber) const{
  stack<const Vertex<D>*> s;
  s.push(&startingVertex);
  
  while(s.empty() == false){
    const Vertex<D>* v = s.top();

    if(visited[v] == false){
      visited[v] = true;
      preNumber[v]=ctr++;
    }
	  
    bool visitedChildren = true;
    for(const Vertex<D>* neighbour : graph.getAdjacentLists(*v)){
      if(visited[neighbour] == false){
        visitedChildren = false;
        s.push(neighbour);
      }
    }
	  
    if(visitedChildren == true){
      s.pop();
      postNumber[v]=ctr++;
    }else{
      // visitedChildren just got visited.
    }    
  }
}

template<class D>
void DFS<D>::traverse(const GraphDirected<D>& graph, 
                      map<const Vertex<D>*, bool>& visited,
                      const Vertex<D>& startingVertex) const{
  stack<const Vertex<D>*> s;
  s.push(&startingVertex);
  
  while(s.empty() == false){
    const Vertex<D>* v = s.top();
    s.pop();
    visited[v] = true;
	  
    for(const Vertex<D>* neighbour : graph.getAdjacentLists(*v)){
      if(visited[neighbour] == false){        
        s.push(neighbour);
      }
    }
  }
}

template<class D>
void DFS<D>::previsit(const GraphDirected<D>& graph, 
                      map<const Vertex<D>*, bool>& visited,
                      const Vertex<D>& vertex,
                      AI::UINT& ctr,
                      map<const Vertex<D>*, AI::UINT>& preNumber,
                      map<const Vertex<D>*, AI::UINT>& postNumber) const{
}

template<class D>
void DFS<D>::postvisit(const GraphDirected<D>& graph,
                       map<const Vertex<D>*, bool>& visited,
                       const Vertex<D>& vertex,
                       AI::UINT& ctr,
                       map<const Vertex<D>*, AI::UINT>& preNumber,
                       map<const Vertex<D>*, AI::UINT>& postNumber) const{
	
}

template<class D>
void DFS<D>::visit(const Vertex<D>* vertex){
}

template<class D>
void DFS<D>::_initializeVisited(const GraphDirected<D>& graph,
                                map<const Vertex<D> *, bool>& visited) const{                            
  for (const Vertex<D>* v : graph.getVertices()) {
    visited[v] = false;
  }
}

template<class D>
void DFS<D>::_traverseAllVertices(const GraphDirected<D>& graph,
                                  map<const Vertex<D> *, bool>& visited) const{
  for(const Vertex<D>* v : graph.getVertices()){
    if(visited[v] == false){
      traverse(graph, visited, *v);
    }
  }
}

template<class D>
void DFS<D>::_traverseAllVertices(const GraphDirected<D>& graph,
                                  map<const Vertex<D> *, bool>& visited,
                                  AI::UINT& ctr,
                                  map<const Vertex<D>*, AI::UINT>& preNumber,
                                  map<const Vertex<D>*, AI::UINT>& postNumber) const{
  for(const Vertex<D>* v : graph.getVertices()){
    if(visited[v] == false){
      traverse(graph, visited, *v, ctr, preNumber, postNumber);
    }
  }
}

}  // namespace Graph
}  // namespace Algorithm.
}  // namespace AI.

#endif /* ALGORITHMS_GRAPH_DFS_H_ */
