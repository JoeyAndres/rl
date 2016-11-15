#include <vector>
#include <iostream>

#include "rl"

#include "../../lib/catch.hpp"

using namespace rl;
using namespace rl::algorithm;
using namespace rl::algorithm;
using namespace std;

SCENARIO("DimensionalInfo represents a dimension in TileCode",
         "[DimensionalInfo]") {
  GIVEN("DimensionalInfo instance") {
    DimensionInfo<rl::FLOAT> dim(-0.5F, 0.5F, 3, 0);


    WHEN ("DimensionalInfo::GetOffsets") {
      THEN ("Returns 1/3") {
        REQUIRE((dim.GetOffsets() - 1.0f/3.0f) < 0.001f);
      }
    }

    WHEN ("DimensionalInfo::GetGridCountReal") {
      THEN ("Returns 4") {
        REQUIRE(dim.GetGridCountReal() == 4);
      }
    }

    WHEN ("DimensionalInfo::GetGridCountIdeal") {
      THEN ("Returns 3") {
        REQUIRE(dim.GetGridCountIdeal() == 3);
      }
    }

    WHEN ("DimensionalInfo::GetRangeDifference") {
      THEN ("Returns 1") {
        REQUIRE((dim.GetRangeDifference() - 1.0f) < 0.001f);
      }
    }

    WHEN ("DimensionalInfo::getGeneralizationScale") {
      THEN ("Returns 0") {
        REQUIRE((dim.getGeneralizationScale() - 0.0f) < 0.001f);
      }
    }
  }
}
