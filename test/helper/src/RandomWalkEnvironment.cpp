/*
 * RandomWalkEnvironment.cpp
 */

#include <iostream>

#include "../include/RandomWalkEnvironment.h"

namespace rl {

RandomWalkEnvironment::RandomWalkEnvironment(
  Actuator<rl::INT>& actuator, Sensor<rl::INT>& sensor) :
    Environment<rl::INT, rl::INT>(actuator, sensor) {
  _env[rl::agent::StateAction<rl::INT, rl::INT>(A, L)] = T;
  _env[rl::agent::StateAction<rl::INT, rl::INT>(A, R)] = B;
  _env[rl::agent::StateAction<rl::INT, rl::INT>(B, L)] = A;
  _env[rl::agent::StateAction<rl::INT, rl::INT>(B, R)] = C;
  _env[rl::agent::StateAction<rl::INT, rl::INT>(C, L)] = B;
  _env[rl::agent::StateAction<rl::INT, rl::INT>(C, R)] = D;
  _env[rl::agent::StateAction<rl::INT, rl::INT>(D, L)] = C;
  _env[rl::agent::StateAction<rl::INT, rl::INT>(D, R)] = T;
}

std::pair<INT, FLOAT> RandomWalkEnvironment::getNextStateAndReward(const StateAction<rl::INT, rl::INT>& stateAction) {
  INT nextState = this->_env[stateAction];

  FLOAT nextReward = -1.0F;
  if (nextState == T) {
    nextReward = 0.0F;
  }

  return { nextState, nextReward };
}

} /* namespace rl */
