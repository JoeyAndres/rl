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
#include <vector>
#include <iostream>

#include "rl"

# Here are files where rl::agent::Environment and rl::agent::Sensor are overidden.
#include "RandomWalkEnvironment.h"
#include "SensorRandomWalk.h"

#include "../../lib/catch.hpp"

using std::vector;

using namespace rl;
using namespace std;

SCENARIO("Sarsa converge to a solution",
         "[rl::Sarsa]") {
  GIVEN("A random walk environment") {
    Actuator <rl::INT> arw({L, R});  // Setup actuator with actions.
    SensorRandomWalk srw;  // Setup sensor.
    srw.addTerminalState(T);  // Setup terminal state.
    rl::RandomWalkEnvironment rwEnv(arw, srw);  // Setup environment.

    policy::EpsilonGreedy <rl::INT, rl::INT> policy(1.0F);
    algorithm::Sarsa <rl::INT, rl::INT> sarsa(0.1F, 0.9F, policy);

    Agent <rl::INT, rl::INT> agent(rwEnv, sarsa);

    WHEN("We do multiple episodes") {
      rl::INT iterationCount = 0;
      for (rl::INT i = 0; i < 100; i++) {
        agent.reset();  // Overloaded to go back to set b.

        iterationCount = agent.executeEpisode();

        THEN("At the end, we solve the random walk environment in 2 iteration") {
          REQUIRE(iterationCount <= 2);
        }
      }
    }
  }
}
```

## Prediction Problem
Taken from AgentSupervised_test.cpp

```c++
#include "rl"

#include "../../lib/catch.hpp"

using namespace std;

SCENARIO("Supervised agent develop an accurate model of the environment.",
         "[rl::AgentSupervised]") {
  GIVEN("A binary environment in which 1 is good and 0 is bad.") {
    rl::policy::EpsilonGreedy<int, int> policy(1.0F);
    rl::algorithm::Sarsa<int, int> sarsaAlgorithm(0.1F, 0.9F, policy);
    auto actionSet = rl::agent::ActionSet<int>({0, 1});
    rl::AgentSupervised<int, int> supevisedAgent(actionSet, sarsaAlgorithm);

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
```

As observed, prediction problem, since the agent don't have to interact with the environment,
but just takes intput. It looks way simpler.
