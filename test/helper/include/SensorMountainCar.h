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

#include <memory>

#include "rl"

using rl::stateCont;
using rl::actionCont;
using rl::agent::Environment;
using rl::agent::spEnvironment;
using rl::agent::Sensor;
using rl::agent::spSensor;
using rl::agent::Actuator;

using std::shared_ptr;

class SensorMountainCar final : public Sensor<stateCont> {
 public:
  SensorMountainCar();
  bool isTerminalState(const rl::spStateCont &stateData) const override;
};

class SensorMountainCarFactory {
 public:
  static spSensor<stateCont> create();
};
