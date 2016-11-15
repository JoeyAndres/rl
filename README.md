rl
===========

[![Build Status](http://ci.joeyandres.com/job/rl-unit-test-master/badge/icon)](http://ci.joeyandres.com/job/rl-unit-test-master/)

Modularized various Reinforcement Learning Algorithm library. 
See test/include and test/src for examples.

Note: This is currently only built for Linux systems. 
Some threading libraries are linux specific (even the latest c++ standard which is supposed to be platform independent).

# Compilation and Installation

### Caveat
**rl** have some minor _double precision floating point_ issues in older compilers and os.
The mountain car problem in test won't converge to a an optimal solution in osx and
old g++ compiler (e.g. g++ 4.2.1). For optimal performance, use linux and new g++ compiler.

### Dependency:
* g++-4.9 or greater or clang.
* cmake 3.2.2 or greater.

### Installing dependencies Ubuntu 16.04:

`sudo apt install g++ cmake`

### Building 
1. `mkdir build`
2. `cd build`
3. `cmake ..`
4. `make -j16`
5. `sudo make install`

# Usage

After install, **rl** is usable in your project by a simple include:

```c++
#include <rl>
```

## Control Problem
For examples, see test. One of the test solves the _Random Walk Problem_ with
the _SARSA_ algorithm. The following is a snippet with a walk through comment:

```c++
# Override `Environment` class for your specific problem.
RandomWalkEnvironment rwe;

# Override the `SensorDiscrete` since Random Walk deals with discrete state space. 
SensorRandomWalk srw(rwe);
# Add a terminal state. (This definition of `T` is not defined in this snippet).
srw.addTerminalState(T);

# Initialize the actuator base. Here we store the possible actions.
ActuatorBase<AI::INT, AI::INT> arw(rwe);
arw.addAction(L);
arw.addAction(R);

# Initialize the policy. Here we use greedy. Other policies exist, such as
# Softmax.
Algorithm::Policy::EpsilonGreedy<AI::INT, AI::INT> policy(1.0F);

# Initialize the sarsa algorithm. We gave it 0.1 step-size and 0.9 discount rate.
Algorithm::RL::Sarsa<AI::INT, AI::INT> sarsaAlgorithm(0.1F, 0.9F, policy);

# Initialize the agent.
Agent<AI::INT, AI::INT> agent(srw, arw, sarsaAlgorithm);

# Execute multiple episodes.
AI::INT iterationCount = 0;
for (AI::INT i = 0; i < 100; i++) {
  rwe.reset();
  iterationCount = agent.executeEpisode();
}
```

## Prediction Problem
Taken from AgentSupervised_test.cpp

```c++
#include "GlobalHeader.h"

#include "Agent.h"
#include "EpsilonGreedy.h"
#include "Sarsa.h"

#include "catch.hpp"

using namespace AI;
using namespace std;

SCENARIO("Supervised agent develop an accurate model of the environment.",
         "[AI::AgentSupervised]") {
  GIVEN("A binary environment in which 1 is good and 0 is bad.") {
    Algorithm::Policy::EpsilonGreedy<int, int> policy(1.0F);
    Algorithm::RL::Sarsa<int, int> sarsaAlgorithm(0.1F, 0.9F, policy);
    auto actionSet = ActionSet<int>({0, 1});
    AgentSupervised<int, int> supevisedAgent(actionSet, sarsaAlgorithm);

    WHEN ("When I train 1 to be good and 0 to be bad") {
      supevisedAgent.train(1, 1, 1000, 1);  // We don't transition anywhere. It's just being in state 1 is good.
      supevisedAgent.train(0, 0, -1000, 0);  // Same deal.

      THEN ("Agent should know that 1 should be good and 0 should be bad") {
        auto value1 = sarsaAlgorithm.getStateActionValue(StateAction<int, int>(1, 1));
        auto value0 = sarsaAlgorithm.getStateActionValue(StateAction<int, int>(0, 0));

        REQUIRE(value1 > value0);
      }
    }
  }
}
```

As observed, prediction problem, since the agent don't have to interact with the environment,
but just takes intput. It looks way simpler.
