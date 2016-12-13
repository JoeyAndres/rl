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
#### Required
* g++-4.9 or greater or clang.
* cmake 3.2.2 or greater.
#### Optional
* [SDM (Sparse Distributed Memory)](https://github.com/JoeyAndres/sdm.git) - If you want to utilize storage servers.

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

#include "catch.hpp"
#include "rl"

#include "RandomWalkEnvironment.h"
#include "SensorRandomWalk.h"

using std::vector;

using rl::policy::EpsilonGreedyFactory;
using rl::agent::ActuatorFactory;
using rl::agent::SensorDiscreteFactory;
using rl::algorithm::SarsaFactory;

SCENARIO("Sarsa converge to a solution",
         "[rl::Sarsa]") {
  GIVEN("A random walk environment") {
// Setup actuator with actions.
    auto arw = ActuatorFactory<rl::INT>({ L, R }).get();
    // Setup sensor.
    auto srw = SensorDiscreteFactory<rl::INT>(B).get();
    srw->addTerminalState(T);  // Setup terminal state.

    // Setup environment.
    auto rwe = RandomWalkEnvironmentFactory(arw, srw).get();

    auto policy = EpsilonGreedyFactory<rl::INT, rl::INT>(1.0F).get();
    auto sarsa = SarsaFactory<rl::INT, rl::INT>(0.1F, 0.9F, policy).get();

    rl::agent::Agent <rl::INT, rl::INT> agent(rwe, sarsa);

    WHEN("We do multiple episodes") {
      rl::INT iterationCount = 0;
      for (rl::INT i = 0; i < 100; i++) {
        agent.reset();  // Overloaded to go back to set b.

        iterationCount = agent.executeEpisode();

        THEN("At the end, we solve the random walk environment in 2 "
               "iteration") {
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

#include "catch.hpp"

using rl::agent::ActionContainerFactory;
using rl::algorithm::SarsaFactory;
using rl::policy::EpsilonGreedyFactory;

SCENARIO("Supervised agent develop an accurate model of the environment.",
         "[rl::agent::AgentSupervised]") {
  GIVEN("A binary environment in which 1 is good and 0 is bad.") {
    rl::spState<int> state0(new int(0));
    rl::spState<int> state1(new int(1));

    rl::spAction<int> action0(new int(0));
    rl::spAction<int> action1(new int(1));

    auto policy = EpsilonGreedyFactory<int, int>(1.0F).get();
    auto sarsaAlgorithm = SarsaFactory<int, int>(0.1F, 0.9F, policy).get();
    auto actionSet = ActionContainerFactory<int>({action0, action1}).get();
    rl::agent::AgentSupervised<int, int> supevisedAgent(actionSet,
                                                        sarsaAlgorithm);

    WHEN("When I train 1 to be good and 0 to be bad") {
      // We don't transition anywhere. It's just being in state 1 is good.
      supevisedAgent.train(state1, action1, 1000, state1);

      // Same deal.
      supevisedAgent.train(state0, action0, -1000, state0);

      THEN("Agent should know that 1 should be good and 0 should be bad") {
        auto value1 = sarsaAlgorithm->getStateActionValue(
          rl::agent::StateAction<int, int>(state1, action1));
        auto value0 = sarsaAlgorithm->getStateActionValue(
          rl::agent::StateAction<int, int>(state0, action0));

        REQUIRE(value1 > value0);
      }
    }
  }
}
```

As observed, prediction problem, since the agent don't have to interact with the environment,
but just takes intput. It looks way simpler.
