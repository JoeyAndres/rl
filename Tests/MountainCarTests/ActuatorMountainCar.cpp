/*
 * ActuatorMountainCar.cpp
 *
 *  Created on: Jun 12, 2014
 *      Author: jandres
 */

#include <cmath>
#include <iostream>

#include "ActuatorMountainCar.h"
#include "MountainCarEnvironment.h"

using namespace std;

namespace AI {

void ActuatorMountainCar::applyAction(const vector<AI::FLOAT>& action) {
	MountainCarEnvironment& mce = MountainCarEnvironment::getInstance();
	mce.applyAction(std::round(action[0]));
}

}
/* namespace AI */
