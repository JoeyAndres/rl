//
// Created by jandres on 12/11/16.
//

#include "rl"

#include "../../lib/catch.hpp"

using namespace std;

SCENARIO("Supervised agent develop an accurate model of the environment.",
         "[rl::agent::AgentSupervised]") {
  GIVEN("A binary environment in which 1 is good and 0 is bad.") {
    rl::policy::EpsilonGreedy<int, int> policy(1.0F);
    rl::algorithm::Sarsa<int, int> sarsaAlgorithm(0.1F, 0.9F, policy);
    auto actionSet = rl::agent::ActionSet<int>({0, 1});
    rl::agent::AgentSupervised<int, int> supevisedAgent(actionSet, sarsaAlgorithm);

    WHEN ("When I train 1 to be good and 0 to be bad") {
      supevisedAgent.train(1, 1, 1000, 1);  // We don't transition anywhere. It's just being in state 1 is good.
      supevisedAgent.train(0, 0, -1000, 0);  // Same deal.

      THEN ("Agent should know that 1 should be good and 0 should be bad") {
        auto value1 = sarsaAlgorithm.getStateActionValue(rl::agent::StateAction<int, int>(1, 1));
        auto value0 = sarsaAlgorithm.getStateActionValue(rl::agent::StateAction<int, int>(0, 0));

        REQUIRE(value1 > value0);
      }
    }
  }
}
