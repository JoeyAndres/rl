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

SCENARIO("TileCodeMurMur retrieves the correct feature vector",
         "[TileCodeMurMur]") {
  GIVEN("TileCodeMurMur instance") {
    vector<DimensionInfo<rl::FLOAT> > dimensionalInfoVector = {
      DimensionInfo<rl::FLOAT>(-0.5F, 0.5F, 3, 0),
      DimensionInfo<rl::FLOAT>(-0.5F, 0.5F, 3, 0)
    };

    TileCodeMurMur tileCode(dimensionalInfoVector, 4, 100);

    WHEN ("TileCodeMurMur::getDimension is called.") {
      THEN ("Returns 3") {
        REQUIRE(tileCode.getDimension() == 2);
      }
    }

    WHEN ("TileCodeMurMur::getSize is called.") {
      THEN ("Returns 100") {
        REQUIRE(tileCode.getSize() == 100);
      }
    }

    // The rest are hash in which I don't want to predict. They are all tested
    // by TileCode_test.cpp anyway.
  }
}
