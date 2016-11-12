rl
===========

Modularized various Reinforcement Learning Algorithm library. 
See test/include and test/src for examples.

Note: This is currently only built for Linux systems. 
Some threading libraries are linux specific (even the latest c++ standard which is supposed to be platform independent).

# Compilation and Installation

### Dependency:
* g++-4.9 or greater.

### Installing dependencies Ubuntu:

`sudo apt install g++`

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

## Prediction Problem (WIP)
At the moment, this is not part of the code. Although possible, it will 
look very ugly.
