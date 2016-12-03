/**
 * rl - Reinforcement Learning
 * Copyright (C) 2016  Joey Andres<yeojserdna@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../include/RandomWalkEnvironment.h"

RandomWalkEnvironment::RandomWalkEnvironment(
  const  spActuator<rl::INT>& actuator,
  const spSensor<rl::INT>& sensor) :
    Environment<rl::INT, rl::INT>(actuator, sensor) {
  _env[rl::agent::StateAction<rl::INT, rl::INT>(::A, ::L)] = ::T;
  _env[rl::agent::StateAction<rl::INT, rl::INT>(::A, ::R)] = ::B;
  _env[rl::agent::StateAction<rl::INT, rl::INT>(::B, ::L)] = ::A;
  _env[rl::agent::StateAction<rl::INT, rl::INT>(::B, ::R)] = ::C;
  _env[rl::agent::StateAction<rl::INT, rl::INT>(::C, ::L)] = ::B;
  _env[rl::agent::StateAction<rl::INT, rl::INT>(::C, ::R)] = ::D;
  _env[rl::agent::StateAction<rl::INT, rl::INT>(::D, ::L)] = ::C;
  _env[rl::agent::StateAction<rl::INT, rl::INT>(::D, ::R)] = ::T;
}

std::pair<rl::spState<rl::INT>, rl::FLOAT>
RandomWalkEnvironment::getNextStateAndReward(
  const rl::agent::StateAction<rl::INT, rl::INT>& stateAction) {
  spState<rl::INT> nextState = this->_env[stateAction];

  rl::FLOAT nextReward = -1.0F;
  if (*nextState == *(::T)) {
    nextReward = 0.0F;
  }

  return { nextState, nextReward };
}

RandomWalkEnvironmentFactory::RandomWalkEnvironmentFactory(
  const spActuator<rl::INT>& actuator,
  const spSensor<rl::INT>& sensor) {
  this->_instance = spEnvironment<rl::INT, rl::INT>(
    new RandomWalkEnvironment(actuator, sensor));
}
