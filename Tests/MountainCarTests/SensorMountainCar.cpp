/*
 * SensorMountainCar.cpp
 *
 *  Created on: Jun 12, 2014
 *      Author: jandres
 */

#include <vector>
#include <iostream>

#include "SensorMountainCar.h"
#include "MountainCarEnvironment.h"

using namespace std;

namespace AI {

vector<AI::FLOAT> SensorMountainCar::getSensorState() {
	MountainCarEnvironment& mce = MountainCarEnvironment::getInstance();
	vector<AI::FLOAT> currentState = mce.getCurrentState();
	return currentState;
}

AI::FLOAT SensorMountainCar::getReward(vector<AI::FLOAT>& sensorState)
		throw (StateNotExistException) {
	(void) sensorState;
	MountainCarEnvironment& mce = MountainCarEnvironment::getInstance();
	return mce._currentReward;;
}

bool SensorMountainCar::isTerminalState(
		const vector<AI::FLOAT>& stateData) const {
	if (abs(stateData[0] - 0.50F) <= 0.01F) {
		return true;
	}

	return false;
}

bool SensorMountainCar::isState(const vector<AI::FLOAT>& state) const {
	(void) state;
	return true;
}

}

/* namespace AI */
