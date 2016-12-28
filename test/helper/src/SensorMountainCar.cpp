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

#include <cmath>

#include "../include/SensorMountainCar.h"
#include "../include/MountainCarEnvironment.h"

SensorMountainCar::SensorMountainCar() :
  rl::agent::Sensor<floatArray<2>>(
    spFloatArray<2>(new floatArray<2>({ 0.0F, 0.0F }))) {
}

bool SensorMountainCar::isTerminalState(
  const spFloatArray<2> &stateData) const {
  if (std::abs(stateData->at(POS) - 0.50F) <= 0.01F) {
    return true;
  }

  return false;
}

rl::agent::spSensor<floatArray<2>> SensorMountainCarFactory::create() {
  return spSensor<floatArray<2>>(new SensorMountainCar);
}
