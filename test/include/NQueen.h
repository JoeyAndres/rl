/**
 * NQueen.h
 */

#pragma once

#include <array>
#include <cstdint>
#include <random>
#include <iostream>
#include <map>

using namespace std;

template <size_t N>
class NQueen{
 public:
  /**
   * Random start state.
   */
  NQueen(bool random=false){
    std::random_device rd;
    std::uniform_int_distribution<size_t> uid(0, N-1);
    
    for(size_t i = 0; i < N; i++){
      _queenPos[i] = uid(rd);
    }
  }

  /**
   * @param queePos start queenPos.
   * @throws Exception if position exceeds [0, N-1].
   */
  NQueen(const array<size_t, N>& queenPos) : _queenPos(queenPos){}

  virtual size_t heuristicCost() const{
    size_t cost = 0;
    for(size_t i = 0; i < N; i++){ cost += _conflict(i); }
    return cost/2;
  }

  array<array<size_t, N>, N*(N-1)> getNextStates() const{
    array<array<size_t, N>, N*(N-1)> rv;
    size_t index = 0;
    for(size_t i = 0; i < N; i++){
      for(size_t j = 0; j < N; j++){
        if(_queenPos.at(i) != j){
          rv[index] = _queenPos;
          rv[index][i] = j;
          index++;
        }
      }
    }

    return rv;
  }

 protected:
  /**
   * @param pos see if queen in index pos is in conflict.
   * @return conflict count.
   */
  virtual size_t _conflict(size_t pos) const{
    // Iterate forward.    
    size_t conflicts = 0;
    int hor, top, bot = 0;
    hor = top = bot = _queenPos[pos]; // Positions that is hit by _queenPos[pos] at index i.
    for(int i = pos+1; i < N; i++){
      if(_queenPos[i] == hor){
        conflicts++;
        continue;
      }
      
      if(top <= N-1 && _queenPos[i] == ++top){
        conflicts++;
        continue;
      }

      if(bot >= 0 && _queenPos[i] == --bot){
        conflicts++;
        continue;
      }
    }

    // Iterate backward.
    hor = top = bot = _queenPos[pos];  // Reset values.
    for(int i = pos-1; i >= 0; i--){
     
      if(_queenPos[i] == hor){
        conflicts++;
        continue;
      }
      
      if(top <= N-1 && _queenPos[i] == ++top){
        conflicts++;
        continue;
      }

      if(bot >= 0 && _queenPos[i] == --bot){
        conflicts++;
        continue;
      }
    }

    return conflicts;
  }
  
 protected:
  array<size_t, N> _queenPos;
};
