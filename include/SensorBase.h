/*
 * SensorStatesAbstract.h
 *
 *  Created on: May 31, 2014
 *      Author: jandres
 * 
 */

#ifndef SENSORS_ABSTRACT_H_
#define SENSORS_ABSTRACT_H_

#include <set>
#include <algorithm>

#include "GlobalHeader.h"

#include "StateNotExistException.h"
#include "Environment.h"

using std::set;
using std::find;

namespace AI {

/*! \class SensorBase
 *  \brief Base and interface class for all Sensor objects.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 *
 *  Base and interface class for all Sensor objects. For sensors with
 *  states of discrete nature, @see SensorBase. Otherwise, use this or
 *  SensorContinuous.
 */
template<class S, class A>
class SensorBase {
 public:
  /**
   * @param env environment object to aggregate.
   */
  SensorBase(Environment<S, A>& env);
  
  /**
   * @return current state of agent in environment.
   */
  virtual const S& getSensorState() const;

  /**
   * @param stateData to determine if it is a terminal state.
   * @return true if its a terminal state.
   */
  virtual bool isTerminalState(const S& stateData) const = 0;

  /**
   * Maps sensorState to its corresponding reward.
   * @param sensorState to be mapped to its corresponding reward.
   * @return reward
   */
  virtual AI::FLOAT getLastObservedReward() const;

 protected:
  Environment<S, A>& _env;  //!< Aggregated Environment.
};

/*! \typedef SensorContinuous
 *  \brief Base class for Sensor with continuous state space.
 */
//typedef SensorBase<vector<AI::FLOAT>, > SensorContinuous;

template<class S, class A>
SensorBase<S, A>::SensorBase(Environment<S, A>& env) : _env(env){
}

template<class S, class A>
const S& SensorBase<S, A>::getSensorState() const{
  return _env.getLastObservedState();
}

template<class S, class A>
AI::FLOAT SensorBase<S, A>::getLastObservedReward() const{
  return _env.getLastObservedReward();
}

} /* namespace AI */

#endif /* SENSORS_ABSTRACT_H_ */
