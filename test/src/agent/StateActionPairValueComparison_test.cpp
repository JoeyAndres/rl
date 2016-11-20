//
// Created by jandres on 12/11/16.
//

#include "rl"

#include "SensorRandomWalk.h"
#include "RandomWalkEnvironment.h"

#include "../../lib/catch.hpp"

using namespace std;

SCENARIO("rl::agent::StateActionPairValueComparison can compaire two state action pair.",
         "[rl::agent::StateActionPairValueComparison]") {
  GIVEN("rl::agent::StateActionPairValueComparison") {
    auto B = rl::spState<int>(new int(rl::RandomWalkEnvironment::State::B));
    auto L = rl::spAction<int>(new int(rl::RandomWalkEnvironment::Action::L));

    auto A = rl::spState<int>(new int(rl::RandomWalkEnvironment::State::A));

    rl::agent::StateActionPairValueComparison<int, int> sapvc;
    auto sav1 = std::pair<rl::agent::StateAction<int, int>, double>(
      rl::agent::StateAction<int, int>(B, L), 1.0F);
    auto sav2 = std::pair<rl::agent::StateAction<int, int>, double>(
      rl::agent::StateAction<int, int>(A, L), 2.0F);

    WHEN ("I compare sa1 and sa2 using rl::agent::StateActionPairValueComparison.") {
      THEN ("It should return sa1 > sa2.") {
        REQUIRE(sapvc(sav2, sav1));
      }
    }
  }
}
