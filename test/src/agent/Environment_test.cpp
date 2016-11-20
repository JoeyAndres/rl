#include "rl"

#include "../../lib/catch.hpp"

using namespace std;

SCENARIO("Environment represents the thing agent interacts with.",
         "[rl::agent::AgentSupervised]") {
  GIVEN("A binary environment in which 1 is good and 0 is bad.") {
    rl::spState<int> state0(new int(0));
    rl::spState<int> state1(new int(1));

    rl::spAction<int> action0(new int(0));
    rl::spAction<int> action1(new int(1));

    rl::policy::EpsilonGreedy<int, int> policy(1.0F);
    rl::algorithm::Sarsa<int, int> sarsaAlgorithm(0.1F, 0.9F, policy);
    auto actionSet = rl::agent::ActionSet<int>(rl::spActionSet<int>({action0, action1}));
    rl::agent::AgentSupervised<int, int> supevisedAgent(actionSet, sarsaAlgorithm);

    WHEN ("When I train 1 to be good and 0 to be bad") {
      supevisedAgent.train(state1, action1, 1000, state1);  // We don't transition anywhere. It's just being in state 1 is good.
      supevisedAgent.train(state0, action0, -1000, state0);  // Same deal.

      THEN ("Agent should know that 1 should be good and 0 should be bad") {
        auto value1 = sarsaAlgorithm.getStateActionValue(rl::agent::StateAction<int, int>(state1, action1));
        auto value0 = sarsaAlgorithm.getStateActionValue(rl::agent::StateAction<int, int>(state0, action0));

        REQUIRE(value1 > value0);
      }
    }
  }
}
