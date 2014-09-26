/*
 * SensorStatesContinous.h
 *
 *  Created on: Jun 17, 2014
 *      Author: jandres
 */

#ifndef SENSORSTATESCONTINOUS_H_
#define SENSORSTATESCONTINOUS_H_

#include "GlobalHeader.h"

#include "SensorStatesAbstract.h"

namespace AI {
  class SensorStatesContinous: public SensorStatesAbstract<vector<AI::FLOAT> > {
	virtual vector<AI::FLOAT> getSensorState() = 0;
	virtual bool isState(const vector<AI::FLOAT>& state) const = 0;
	virtual bool isTerminalState(const vector<AI::FLOAT>& stateData) const = 0;

	/**
	 * Maps sensorState to its corresponding reward.
	 * @param sensorState to be mapped to its corresponding reward.
	 * @return reward
	 */
	virtual AI::FLOAT getReward(vector<AI::FLOAT>& sensorState)
		throw (StateNotExistException) = 0;
  };
} /* namespace AI */

#endif /* SENSORSTATESCONTINOUS_H_ */
