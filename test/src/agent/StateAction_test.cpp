/**
 * StateAction_test.cpp
 */

#include "rl"

#include "../../lib/catch.hpp"

SCENARIO("StateAction data type","[rl::agent::StateAction") {
  GIVEN("StateAction instance") {
    rl::agent::StateAction<rl::INT, rl::INT> stateAction(10, 10);
    WHEN("Accessor method are invoked") {
      THEN("Retrieves appropriate value") {
        REQUIRE(stateAction.getState() == 10);
        REQUIRE(stateAction.getAction() == 10);
      }
    }
  }

  GIVEN("Multiple StateAction instance") {
    rl::agent::StateAction<rl::INT, rl::INT> stateAction01(10, 10);
    rl::agent::StateAction<rl::INT, rl::INT> stateAction02(10, 10);
    rl::agent::StateAction<rl::INT, rl::INT> stateAction03(20, 10);
    WHEN("Equality operator is invoked") {
      THEN("Returns true.") {
        REQUIRE(stateAction01 == stateAction02);
        REQUIRE(stateAction01 != stateAction03);
        REQUIRE(stateAction02 != stateAction03);
      }
    }
  }

  GIVEN("Multiple StateAction instance") {
    rl::agent::StateAction<rl::INT, rl::INT> stateAction01(10, 10);
    rl::agent::StateAction<rl::INT, rl::INT> stateAction02(10, 20);
    rl::agent::StateAction<rl::INT, rl::INT> stateAction03(10, 20);
    rl::agent::StateAction<rl::INT, rl::INT> stateAction04(20, 10);
    WHEN("Less operator is invoked") {
      THEN("Compares lexically <S, A>.") {
        REQUIRE(stateAction01 != stateAction02);
        REQUIRE(stateAction01 < stateAction02);
        REQUIRE(stateAction03 != stateAction04);
        REQUIRE(stateAction03 < stateAction04);
      }
    }
  }
}
