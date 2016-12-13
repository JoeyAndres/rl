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

#include <set>
#include <algorithm>
#include <cmath>
#include <memory>

#include "../declares.h"

using std::set;
using std::find;
using std::shared_ptr;

namespace rl {
namespace agent {

/*! \class Sensor
 *  \brief Base and interface class for all Sensor objects.
 *  \tparam S State data type.
 *
 *  Base and interface class for all Sensor objects. For sensors with
 *  states of discrete nature, @see Sensor. Otherwise, use this or
 *  SensorContinuous.
 */
template<class S>
class Sensor {
 public:
  explicit Sensor(const spState<S> &initialState);

  /**
   * @return current state of agent in environment.
   */
  virtual const spState<S> &getLastObservedState() const;

  /**
   * Maps sensorState to its corresponding reward.
   * @param sensorState to be mapped to its corresponding reward.
   * @return reward
   */
  virtual rl::FLOAT getLastObservedReward() const;

  /**
   * Set the last observed state.
   * @param s Last observed state.
   */
  virtual void setLastObservedState(const spState<S> &s);

  /**
   * Changes initial state.
   * @param s New initial state.
   */
  virtual void setInitialState(const spState<S> &s);

  /**
   * Set the last observed reward
   * @param r Last observed reward
   */
  virtual void setLastObservedReward(FLOAT r);

  /**
   * Set last observed state and reward.
   * @param stateAndReward pair of state and reward.
   */
  virtual void setLastObservedStateAndReward(
    const spStateAndReward<S> &stateAndReward);

  /**
   * Resets last observed state to initial state.
   */
  virtual void reset();

  /**
   * @param stateData to determine if it is a terminal state.
   * @return true if its a terminal state.
   */
  virtual bool isTerminalState(const spState<S> &stateData) const = 0;

 private:
  FLOAT _lastObservedReward = NAN;
  spState<S> _initialState;
  spState<S> _lastObservedState;
};

/*! \class spSensor
 *  \brief Sensor wrapped in shared_ptr.
 *  \tparam S Sensor data type.
 */
template<class S>
using spSensor = shared_ptr<Sensor<S>>;

template<class S>
Sensor<S>::Sensor(const spState<S> &initialState) :
  _initialState(initialState),
  _lastObservedState(_initialState) {
}

template<class S>
const spState<S> &Sensor<S>::getLastObservedState() const {
  return this->_lastObservedState;
}

template<class S>
rl::FLOAT Sensor<S>::getLastObservedReward() const {
  return this->_lastObservedReward;
}

template<class S>
void Sensor<S>::setLastObservedState(const spState<S> &s) {
  this->_lastObservedState = s;
}

template<class S>
void Sensor<S>::setInitialState(const spState<S> &s) {
  this->_initialState = s;
}

template<class S>
void Sensor<S>::setLastObservedReward(FLOAT r) {
  this->_lastObservedReward = r;
}

template<class S>
void Sensor<S>::setLastObservedStateAndReward(
  const spStateAndReward<S> &stateAndReward) {
  this->setLastObservedState(std::get<0>(stateAndReward));
  this->setLastObservedReward(std::get<1>(stateAndReward));
}

template<class S>
void Sensor<S>::reset() {
  this->_lastObservedState = this->_initialState;
}

}  // namespace agent
}  // namespace rl
