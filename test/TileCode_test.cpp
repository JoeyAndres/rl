/*
 * TileCode_test.cpp
 *
 *  Created on: Nov 11, 2014
 *      Author: jandres
 */

#include "GlobalHeader.h"

#include <vector>
#include <iostream>

#include <ctime>
#include <ratio>
#include <chrono>

#include "UnitTest++.h"
#include "TileCodeCorrect.h"

using namespace AI;
using namespace AI::Algorithm;
using namespace AI::Algorithm::SL;
using namespace std::chrono;
using namespace std;

void printfv(FEATURE_VECTOR& fv) {
  cout << "( ";
  for (auto v : fv) {
    cout << v << ", ";
  }
  cout << " )" << endl;
}

TEST(TileCodeInit) {
  vector<DimensionInfo<AI::FLOAT> > dimensionalInfoVector = { DimensionInfo<
      AI::FLOAT>(-1.2F, 0.5F, 10), DimensionInfo<AI::FLOAT>(-0.07F, 0.07F, 10),
      DimensionInfo<AI::FLOAT>(0.0F, 2.0F, 3) };
  dimensionalInfoVector[2].setGeneralizationScale(0.0F);
  TileCodeCorrect tileCode(dimensionalInfoVector, 6);

  FEATURE_VECTOR fv;
  tileCode.getFeatureVector(STATE_CONT( { -1.2, -0.07, 0 }), fv);
  printfv(fv);
  fv.clear();
  tileCode.getFeatureVector(STATE_CONT( { 0.5, 0.07, 2 }), fv);
  printfv(fv);
  fv.clear();
  tileCode.getFeatureVector(STATE_CONT( { 0.0, 0.00, 1 }), fv);
  printfv(fv);
}

int main(void) {
  return UnitTest::RunAllTests();
}
