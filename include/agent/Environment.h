/*
 * Environment.h
 *
 *  Created on: Nov 16, 2014
 *      Author: Joey Andres
 */

#pragma once

#include <utility>

#include "../declares.h"
#include "StateAction.h"
#include "Actuator.h"
#include "Sensor.h"

namespace rl {
namespace agent {

template<class S, class A>
/*! \class Environment
 * \brief A module that maps a state-action to next-state and reward.
 *
 * All Environment class will override this class be itself.
 */
class Environment {
 public:
  using SA = StateAction<S, A>;

 public:
  Environment(Actuator<A> &actuator, Sensor<S> &sensor);

  /**
   * @param stateAction Given this state-action, gives next state and reward.
   * @return Next state and reward.
   */
  virtual spStateAndReward<S> getNextStateAndReward(const SA &stateAction) = 0;

  /**
   * @see Actuator Documentation for example.
   * @param action to be applied to environment.
   */
  virtual spStateAndReward<S> applyAction(const spAction<A> &action);

  Actuator<A> &getActuator();
  const Actuator<A> &getActuator() const;

  Sensor<S> &getSensor();
  const Sensor<S> &getSensor() const;

  /**
   * Call when environment is reset.
   */
  virtual void reset();

 protected:
  Actuator<A> &_actuator;
  Sensor<S> &_sensor;
};

template<class S, class A>
inline Environment<S, A>::Environment(Actuator<A> &actuator, Sensor<S> &sensor)
  : _actuator(actuator),
    _sensor(sensor) {
}

template<class S, class A>
spStateAndReward<S> Environment<S, A>::applyAction(const spAction<A> &action) {
  spState<S> currentState = this->_sensor.getLastObservedState();
  StateAction<S, A> currentStateAction (currentState, action);
  spStateAndReward<S> nextStateAndReward = this->getNextStateAndReward(currentStateAction);
  this->_sensor.setLastObservedStateAndReward(nextStateAndReward);

  return nextStateAndReward;
}

template<class S, class A>
Actuator<A> &Environment<S, A>::getActuator() {
  return this->_actuator;
}

template<class S, class A>
const Actuator<A> &Environment<S, A>::getActuator() const {
  return this->_actuator;
}

template<class S, class A>
Sensor<S> &Environment<S, A>::getSensor() {
  return this->_sensor;
}

template<class S, class A>
const Sensor<S> &Environment<S, A>::getSensor() const {
  return this->_sensor;
}

template<class S, class A>
void Environment<S, A>::reset() {
  return this->_sensor.reset();
}

}  // namespace agent
}  // namespace rl
