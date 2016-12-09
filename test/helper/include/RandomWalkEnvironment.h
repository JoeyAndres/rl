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

#pragma once

#include <map>
#include <utility>

#include "rl"

using std::map;
using std::pair;

using rl::spState;
using rl::agent::Environment;
using rl::agent::spEnvironment;
using rl::agent::spSensor;
using rl::agent::spActuator;

const rl::spState<rl::INT>
  A(new rl::INT(0)),
  B(new rl::INT(1)),
  C(new rl::INT(2)),
  D(new rl::INT(3)),
  T(new rl::INT(4));
const rl::spAction<rl::INT> L(new rl::INT(0)), R(new rl::INT(1));

class RandomWalkEnvironment : public Environment<rl::INT, rl::INT>{
 public:
  enum State : int { A = 0, B, C, D, T };
  enum Action : int { L = 0, R };

 public:
  RandomWalkEnvironment(
    const spActuator<rl::INT>& actuator,
    const spSensor<rl::INT>& sensor);

  pair<spState<rl::INT>, rl::FLOAT> getNextStateAndReward(
    const StateAction<rl::INT, rl::INT>& stateAction) override;

 protected:
  map<StateAction<rl::INT, rl::INT>, spState<rl::INT>> _env;
};

class RandomWalkEnvironmentFactory :
  public rl::FactoryAbstract<Environment<rl::INT, rl::INT>>{
 public:
  RandomWalkEnvironmentFactory(
    const spActuator<rl::INT>& actuator,
    const spSensor<rl::INT>& sensor);
};
