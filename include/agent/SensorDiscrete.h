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

#include "Sensor.h"

namespace rl {
namespace agent {

/*! \class SensorDiscrete
 *  \brief Base class for sensors of discrete nature.
 *  \tparam S State data type that is discrete, e.g. rl::UINT,
 *          rl::INT, etc.
 *
 *  Base class for sensors of discrete nature.
 */
template<class S>
class SensorDiscrete : public Sensor<S> {
 public:
  using Sensor<S>::Sensor;

  bool isTerminalState(const spState<S> &stateData) const override;

  /**
   * @param terminalData new terminal state to be added.
   */
  virtual void addTerminalState(const spState<S> &terminalData);

 private:
  spStateSet<S> _terminalStates;  // Must know when to stop.
};

/*! \class spSensorDiscrete
 *  \brief SensorDiscrete wrapped in shared_ptr.
 *  \tparam S Sensor data type.
 */
template<class S>
using spSensorDiscrete = shared_ptr<SensorDiscrete<S>>;

template<class S>
bool SensorDiscrete<S>::isTerminalState(
  const spState<S> &stateData) const {
  return _terminalStates.find(stateData) != _terminalStates.end();
}

template<class S>
void SensorDiscrete<S>::addTerminalState(
  const spState<S> &terminalData) {
  _terminalStates.insert(terminalData);
}

}  // namespace agent
}  // namespace rl
