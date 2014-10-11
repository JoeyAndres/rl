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

ActuatorMountainCar::ActuatorMountainCar() {

}

ActuatorMountainCar::ActuatorMountainCar(set<ACTION_CONT> actionSet)
    : Actuator<ACTION_CONT>(actionSet) {
}

void ActuatorMountainCar::applyAction(const ACTION_CONT& action) {
  MountainCarEnvironment& mce = MountainCarEnvironment::getInstance();
  mce.applyAction(std::round(action[0]));
}

}
/* namespace AI */
