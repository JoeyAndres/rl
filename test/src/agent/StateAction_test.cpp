/**
 * StateAction_test.cpp
 */

#include "rl"

#include "../../lib/catch.hpp"

SCENARIO("StateAction data type","[rl::agent::StateAction") {
  auto state01 = rl::spState<rl::INT>(new rl::INT(10));
  auto action01 = rl::spAction<rl::INT>(new rl::INT(10));

  auto state02 = rl::spState<rl::INT>(new rl::INT(20));
  auto action02 = rl::spAction<rl::INT>(new rl::INT(20));

  GIVEN("StateAction instance") {
    rl::agent::StateAction<rl::INT, rl::INT> stateAction(state01, action01);
    WHEN("Accessor method are invoked") {
      THEN("Retrieves appropriate value") {
        REQUIRE(stateAction.getState() == state01);
        REQUIRE(stateAction.getAction() == action01);
      }
    }
  }

  GIVEN("Multiple StateAction instance") {
    rl::agent::StateAction<rl::INT, rl::INT> stateAction01(state01, action01);
    rl::agent::StateAction<rl::INT, rl::INT> stateAction02(state01, action01);
    rl::agent::StateAction<rl::INT, rl::INT> stateAction03(state02, action01);
    WHEN("Equality operator is invoked") {
      THEN("Returns true.") {
        REQUIRE(stateAction01 == stateAction02);
        REQUIRE(stateAction01 != stateAction03);
        REQUIRE(stateAction02 != stateAction03);
      }
    }
  }

  GIVEN("Multiple StateAction instance") {
    rl::agent::StateAction<rl::INT, rl::INT> stateAction01(state01, action01);
    rl::agent::StateAction<rl::INT, rl::INT> stateAction02(state01, action02);
    rl::agent::StateAction<rl::INT, rl::INT> stateAction03(state01, action02);
    rl::agent::StateAction<rl::INT, rl::INT> stateAction04(state02, action01);
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
