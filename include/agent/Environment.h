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

#include <utility>
#include <memory>

#include "../declares.h"
#include "StateAction.h"
#include "ActuatorFactory.h"
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
  Environment(const spActuator<A> &actuator,
              const spSensor<S> &sensor);

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

  spActuator<A> &getActuator();
  const spActuator<A> &getActuator() const;

  spSensor<S> &getSensor();
  const spSensor<S> &getSensor() const;

  /**
   * Call when environment is reset.
   */
  virtual void reset();

 protected:
  spActuator<A> _actuator;
  spSensor<S> _sensor;
};

template<class S, class A>
using spEnvironment = shared_ptr<Environment<S, A>>;

template<class S, class A>
Environment<S, A>::Environment(
  const spActuator<A> &actuator,
  const spSensor<S> &sensor)
  : _actuator(actuator),
    _sensor(sensor) {
}

template<class S, class A>
spStateAndReward<S> Environment<S, A>::applyAction(const spAction<A> &action) {
  spState<S> currentState = this->_sensor->getLastObservedState();
  StateAction<S, A> currentStateAction(currentState, action);
  spStateAndReward<S> nextStateAndReward = this->getNextStateAndReward(
    currentStateAction);
  this->_sensor->setLastObservedStateAndReward(nextStateAndReward);

  return nextStateAndReward;
}

template<class S, class A>
spActuator<A> &Environment<S, A>::getActuator() {
  return this->_actuator;
}

template<class S, class A>
const spActuator<A> &Environment<S, A>::getActuator() const {
  return this->_actuator;
}

template<class S, class A>
spSensor<S> &Environment<S, A>::getSensor() {
  return this->_sensor;
}

template<class S, class A>
const spSensor<S> &Environment<S, A>::getSensor() const {
  return this->_sensor;
}

template<class S, class A>
void Environment<S, A>::reset() {
  return this->_sensor->reset();
}

}  // namespace agent
}  // namespace rl
