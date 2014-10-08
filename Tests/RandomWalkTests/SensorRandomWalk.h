/*
 * SensorRandomWalk.h
 *
 *  Created on: Jun 1, 2014
 *      Author: jandres
 */

#ifndef SENSORRANDOMWALK_H_
#define SENSORRANDOMWALK_H_

#include "SensorStatesDiscrete.h"

namespace AI {

template<class SensorData>
class SensorRandomWalk final : public SensorStatesDiscrete<SensorData> {
	virtual SensorData getSensorState() = 0;
};

template<>
class SensorRandomWalk<AI::INT> final : public SensorStatesDiscrete<AI::INT> {
public:
	virtual AI::INT getSensorState();
	virtual AI::FLOAT getReward(AI::INT& sensorState)
			throw (StateNotExistException);
};
} /* namespace AI */

#endif /* SENSORRANDOMWALK_H_ */
