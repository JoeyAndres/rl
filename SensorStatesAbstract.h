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

  template<class SensorData>
  class SensorStatesAbstract {
  public:
	virtual SensorData getSensorState() = 0;
	virtual bool isState(const SensorData& state) const = 0;
	virtual bool isTerminalState(const SensorData& stateData) const = 0;

	/**
	 * Maps sensorState to its corresponding reward.
	 * @param sensorState to be mapped to its corresponding reward.
	 * @return reward
	 */
	virtual AI::FLOAT getReward(SensorData& sensorState)
		throw (StateNotExistException) = 0;

  };
} /* namespace AI */

#endif /* SENSORS_ABSTRACT_H_ */
