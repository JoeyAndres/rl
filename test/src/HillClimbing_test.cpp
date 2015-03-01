/**
 * HillClimbing_test.cpp
 */

#include <cppunit/TestAssert.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <random>

#include "HillClimbing_test.h"
#include "NQueen.h"

using namespace std;

bool myfn(const array<size_t, 8>& i, const array<size_t, 8>& j) {
  return NQueen<8>(i).heuristicCost() < NQueen<8>(j).heuristicCost();
}

array<size_t, 8> maxElem(const array<array<size_t, 8>, 56>& arr){
  return *std::min_element(arr.begin(), arr.end(), myfn);
}

void HillClimbing_test::EightQueenSearchTest(){
  NQueen<8> joey({3, 2, 1, 4, 3, 2, 1, 2});
  cout << NQueen<8>(maxElem(joey.getNextStates())).heuristicCost() << endl;

  for(auto i : maxElem(joey.getNextStates())){
    cout << i << ' ';
  }
  cout << endl;

  std::random_device rd;
  std::uniform_int_distribution<size_t> uid(0, 7);

  array<size_t, 8> c = {uid(rd), uid(rd), uid(rd), uid(rd), uid(rd), uid(rd), uid(rd), uid(rd)};
  cout << "cost: " << NQueen<8>(c).heuristicCost() << endl;

  while(true){
    array<size_t, 8> n = maxElem(NQueen<8>(c).getNextStates());
    if(NQueen<8>(n).heuristicCost() >= NQueen<8>(c).heuristicCost())
      if(NQueen<8>(c).heuristicCost() != 0){
        // rand restart.
        n = {uid(rd), uid(rd), uid(rd), uid(rd), uid(rd), uid(rd), uid(rd), uid(rd)};
      }else{
        break;
      }
    c = n;
    
    cout << "cost: " << NQueen<8>(c).heuristicCost() << endl;
  }

  cout << "cost: " << NQueen<8>(c).heuristicCost() << endl;

  for(auto i : c){
    cout << i << ' ';
  }

  cout << endl;
}
