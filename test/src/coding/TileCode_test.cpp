/*
 * TileCode_test.cpp
 *
 *  Created on: Nov 11, 2014
 *      Author: jandres
 */

#include <vector>
#include <iostream>

#include "rl"

#include "../../lib/catch.hpp"

using namespace rl;
using namespace rl::algorithm;
using namespace rl::algorithm;
using namespace std;

SCENARIO("Tile code retrieves the correct feature vector",
         "[TileCodeCorrect]") {
  GIVEN("TileCodeCorrect instance") {
    vector<DimensionInfo<rl::FLOAT> > dimensionalInfoVector = {
      DimensionInfo<rl::FLOAT>(-0.5F, 0.5F, 3, 0),
      DimensionInfo<rl::FLOAT>(-0.5F, 0.5F, 3, 0)
    };

    TileCodeCorrect tileCode(dimensionalInfoVector, 4);

    WHEN ("TileCode::getDimension is called.") {
      THEN ("Returns 3") {
        REQUIRE(tileCode.getDimension() == 2);
      }
    }

    WHEN ("TileCode::getSize is called.") {
      THEN ("Returns (3+1)*(3*1)*4 = 16*4") {
        REQUIRE(tileCode.getSize() == 16*4);
      }
    }

    // TODO: Get all data of paramToGridValue
    WHEN ("TileCode::paramToGridValue is called for -0.4.") {
      THEN ("Return 0") {
        REQUIRE(tileCode.paramToGridValue(-0.4, 1, 1) == 0);
      }
    }

    WHEN ("TileCode::getFeatureVector is called for (-0.4, -0.4).") {
      THEN ("Return (0, 16, 32, 48)") {
        auto fv = tileCode.getFeatureVector(stateCont({-0.4, -0.4}));
        decltype(fv) result { 0, 16, 32, 48 };
        REQUIRE(fv == result);
      }
    }
  }
}
