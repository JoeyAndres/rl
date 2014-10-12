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

using std::set;
using std::find;

namespace AI {

/*! \class SensorBase
 *  \brief Base and interface class for all Sensor objects.
 *  \tparam SensorData State data type.
 *
 *  Base and interface class for all Sensor objects. For sensors with
 *  states of discrete nature, @see SensorBase. Otherwise, use this or
 *  SensorContinuous.
 */
template<class SensorData>
class SensorBase {
 public:
  /**
   * @return current state of agent in environment.
   */
  virtual SensorData getSensorState() = 0;

  /**
   * @param state to determine if its in state space.
   * @return true if state is domain in state space.
   */
  virtual bool isState(const SensorData& state) const = 0;

  /**
   * @param stateData to determine if it is a terminal state.
   * @return true if its a terminal state.
   */
  virtual bool isTerminalState(const SensorData& stateData) const = 0;

  /**
   * Maps sensorState to its corresponding reward.
   * @param sensorState to be mapped to its corresponding reward.
   * @return reward
   */
  virtual AI::FLOAT getReward(SensorData& sensorState)
      throw (StateNotExistException) = 0;

};

/*! \typedef SensorContinuous
 *  \brief Base class for Sensor with continuous state space.
 */
typedef SensorBase<vector<AI::FLOAT> > SensorContinuous;

} /* namespace AI */

#endif /* SENSORS_ABSTRACT_H_ */
