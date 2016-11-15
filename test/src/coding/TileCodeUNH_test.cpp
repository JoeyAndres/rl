#include <vector>
#include <iostream>

#include "rl"

#include "../../lib/catch.hpp"

using namespace rl;
using namespace rl::algorithm;
using namespace rl::algorithm;
using namespace std;

SCENARIO("TileCodeUNH retrieves the correct feature vector",
         "[TileCodeUNH]") {
  GIVEN("TileCodeUNH instance") {
    vector<DimensionInfo<rl::FLOAT> > dimensionalInfoVector = {
      DimensionInfo<rl::FLOAT>(-0.5F, 0.5F, 3, 0),
      DimensionInfo<rl::FLOAT>(-0.5F, 0.5F, 3, 0)
    };

    TileCodeUNH tileCode(dimensionalInfoVector, 4, 100);

    WHEN ("TileCodeUNH::getDimension is called.") {
      THEN ("Returns 3") {
        REQUIRE(tileCode.getDimension() == 2);
      }
    }

    WHEN ("TileCodeUNH::getSize is called.") {
      THEN ("Returns 100") {
        REQUIRE(tileCode.getSize() == 100);
      }
    }

    // The rest are hash in which I don't want to predict. They are all tested
    // by TileCode_test.cpp anyway.
  }
}
