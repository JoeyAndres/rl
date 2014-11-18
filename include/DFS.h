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
  
  virtual void traverse(GraphDirected<D>& graph,
                        map<const Vertex<D>*, bool>& visited,
                        const Vertex<D>& startingVertex,
                        AI::UINT& ctr,
                        map<const Vertex<D>*, AI::UINT>& preNumber, 
                        map<const Vertex<D>*, AI::UINT>& postNumber) const;
  
  virtual void traverse(GraphDirected<D>& graph,
                        map<const Vertex<D>*, bool>& visited,
                        const Vertex<D>& startingVertex) const;
 
  virtual void previsit(GraphDirected<D>& graph, 
                        map<const Vertex<D>*, bool>& visited,
                        const Vertex<D>& vertex,
                        AI::UINT& ctr,
                        map<const Vertex<D>*, AI::UINT>& preNumber,
                        map<const Vertex<D>*, AI::UINT>& postNumber) const;
  virtual void postvisit(GraphDirected<D>& graph,
                         map<const Vertex<D>*, bool>& visited,
                         const Vertex<D>& vertex,
                         AI::UINT& ctr,
                         map<const Vertex<D>*, AI::UINT>& preNumber,
                         map<const Vertex<D>*, AI::UINT>& postNumber) const;
  virtual void visit(const Vertex<D>* vertex);
};

template<class D>
DFS<D>::DFS(){}

template<class D>
DFS<D>::~DFS() {}

template<class D>
void DFS<D>::search(GraphDirected<D>& graph,
                    map<const Vertex<D>*, AI::UINT>& preNumber,
                    map<const Vertex<D>*, AI::UINT>& postNumber) const{
  AI::UINT ctr = 0;

  // Initialize visited map.
  map<const Vertex<D>*, bool> visited;
  for(const Vertex<D>* v : graph.getVertices()){
    visited[v] = false;
    postNumber[v] = 0;
    preNumber[v] = 0;
  }
	
  // Try traversing to each vertex.
  for(const Vertex<D>* v : graph.getVertices()){
    if(visited[v] == false){
      traverse(graph, visited, *v, ctr, preNumber, postNumber);
    }
  }
}

template<class D>
void DFS<D>::search(GraphDirected<D>& graph) const{
  // Initialize visited map.
  map<const Vertex<D>*, bool> visited;
  for(const Vertex<D>* v : graph.getVertices()){
    visited[v] = false;
  }
	
  // Try traversing to each vertex.
  for(const Vertex<D>* v : graph.getVertices()){
    if(visited[v] == false){
      traverse(graph, visited, *v);
    }
  }
}

template<class D>
void DFS<D>::search(GraphDirected<D>& graph,
                    const Vertex<D>& startingVertex,
                    map<const Vertex<D>*, AI::UINT>& preNumber,
                    map<const Vertex<D>*, AI::UINT>& postNumber) const{
  AI::UINT ctr = 0;

  // Initialize visited map.
  map<const Vertex<D>*, bool> visited;
  for(const Vertex<D>* v : graph.getVertices()){
    visited[v] = false;
    postNumber[v] = 0;
    preNumber[v] = 0;
  }

  // Traverse startingVertex.
  traverse(graph, visited, startingVertex, ctr, preNumber, postNumber);
	
  // Try traversing to each vertex.
  for(const Vertex<D>* v : graph.getVertices()){
    if(visited[v] == false){
      traverse(graph, visited, *v, ctr, preNumber, postNumber);
    }
  }
}

template<class D>
void DFS<D>::search(GraphDirected<D>& graph, const Vertex<D>& startingVertex) const{
  // Initialize visited map.
  map<const Vertex<D>*, bool> visited;
  for(const Vertex<D>* v : graph.getVertices()){
    visited[v] = false;
  }

  // Traverse startingVertex.
  traverse(graph, visited, startingVertex);
	
  // Try traversing to each vertex.
  for(const Vertex<D>* v : graph.getVertices()){
    if(visited[v] == false){
      traverse(graph, visited, *v);
    }
  }
}
      
template<class D>
void DFS<D>::traverse(GraphDirected<D>& graph, 
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
void DFS<D>::traverse(GraphDirected<D>& graph, 
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
void DFS<D>::previsit(GraphDirected<D>& graph, 
                      map<const Vertex<D>*, bool>& visited,
                      const Vertex<D>& vertex,
                      AI::UINT& ctr,
                      map<const Vertex<D>*, AI::UINT>& preNumber,
                      map<const Vertex<D>*, AI::UINT>& postNumber) const{
  
}

template<class D>
void DFS<D>::postvisit(GraphDirected<D>& graph,
                       map<const Vertex<D>*, bool>& visited,
                       const Vertex<D>& vertex,
                       AI::UINT& ctr,
                       map<const Vertex<D>*, AI::UINT>& preNumber,
                       map<const Vertex<D>*, AI::UINT>& postNumber) const{
	
}

template<class D>
void DFS<D>::visit(const Vertex<D>* vertex){
}

}  // namespace Graph
}  // namespace Algorithm.
}  // namespace AI.

#endif /* ALGORITHMS_GRAPH_DFS_H_ */
