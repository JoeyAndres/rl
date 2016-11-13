/*
 * TileCode_test.cpp
 *
 *  Created on: Nov 11, 2014
 *      Author: jandres
 */

#include "declares.h"

#include <vector>
#include <iostream>

#include "TileCodeCorrect.h"

#include "catch.hpp"

using namespace AI;
using namespace AI::Algorithm;
using namespace AI::Algorithm::SL;
using namespace std;

// Todo: move this to TileCode file. // ostream overload.
void printfv(FEATURE_VECTOR& fv) {
  cout << "( ";
  for (auto v : fv) {
    cout << v << ", ";
  }
  cout << " )" << endl;
}

// TODO: Make a concrete example. Something small so we can actually write it in paper.
SCENARIO("Tile code retrieves the correct feature vector",
         "[TileCodeCorrect]") {
  vector<DimensionInfo<AI::FLOAT> > dimensionalInfoVector = {
    DimensionInfo<AI::FLOAT>(-1.2F, 0.5F, 10),
    DimensionInfo<AI::FLOAT>(-0.07F, 0.07F, 10),
    DimensionInfo<AI::FLOAT>(0.0F, 2.0F, 3, 0.0F)
  };
  
  TileCodeCorrect tileCode(dimensionalInfoVector, 6);

  FEATURE_VECTOR fv = tileCode.getFeatureVector(STATE_CONT( { -1.2, -0.07, 0 }));
  //printfv(fv);
  fv = tileCode.getFeatureVector(STATE_CONT( { 0.5, 0.07, 2 }));
  //printfv(fv);
  fv = tileCode.getFeatureVector(STATE_CONT( { 0.0, 0.00, 1 }));
  //printfv(fv);
}
