/*
 * SensorStatesAbstract.h
 *
 *  Created on: May 31, 2014
 *      Author: jandres
 * 
 */

#pragma once

#include <set>
#include <algorithm>
#include <cmath>

#include "../declares.h"

using std::set;
using std::find;

namespace rl {
namespace agent {

/*! \class Sensor
 *  \brief Base and interface class for all Sensor objects.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 *
 *  Base and interface class for all Sensor objects. For sensors with
 *  states of discrete nature, @see Sensor. Otherwise, use this or
 *  SensorContinuous.
 */
template<class S>
class Sensor {
 public:
  Sensor(const S &initialState);

  /**
   * @return current state of agent in environment.
   */
  virtual const S &getLastObservedState() const;

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
  virtual void setLastObservedState(const S &s);

  /**
   * Changes initial state.
   * @param s New initial state.
   */
  virtual void setInitialState(const S &s);

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
    const StateAndReward<S> &stateAndReward);

  /**
   * Resets last observed state to initial state.
   */
  virtual void reset();

  /**
   * @param stateData to determine if it is a terminal state.
   * @return true if its a terminal state.
   */
  virtual bool isTerminalState(const S &stateData) const = 0;

 private:
  FLOAT _lastObservedReward = NAN;
  S _initialState;
  S _lastObservedState;
};

template<class S>
Sensor<S>::Sensor(const S &initialState) :
  _initialState(initialState),
  _lastObservedState(_initialState) {
}

template<class S>
const S &Sensor<S>::getLastObservedState() const {
  return this->_lastObservedState;
}

template<class S>
rl::FLOAT Sensor<S>::getLastObservedReward() const {
  return this->_lastObservedReward;
}

template<class S>
void Sensor<S>::setLastObservedState(const S &s) {
  this->_lastObservedState = s;
}

template<class S>
void Sensor<S>::setInitialState(const S &s) {
  this->_initialState = s;
}

template<class S>
void Sensor<S>::setLastObservedReward(FLOAT r) {
  this->_lastObservedReward = r;
}

template<class S>
void Sensor<S>::setLastObservedStateAndReward(
  const StateAndReward<S> &stateAndReward) {
  this->setLastObservedState(std::get<0>(stateAndReward));
  this->setLastObservedReward(std::get<1>(stateAndReward));
}

template<class S>
void Sensor<S>::reset() {
  this->_lastObservedState = this->_initialState;
}

}  // namespace agent
}  // namespace rl
