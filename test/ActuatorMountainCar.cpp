/*
 * ActuatorMountainCar.cpp
 *
 *  Created on: Jun 12, 2014
 *      Author: jandres
 */

#include "../test/ActuatorMountainCar.h"

#include <cmath>
#include <iostream>

#include "../test/MountainCarEnvironment.h"

using namespace std;

namespace AI {

ActuatorMountainCar::ActuatorMountainCar() {

}

ActuatorMountainCar::ActuatorMountainCar(set<ACTION_CONT> actionSet)
    : ActuatorBase<ACTION_CONT>(actionSet) {
}

void ActuatorMountainCar::applyAction(const ACTION_CONT& action) {
  MountainCarEnvironment& mce = MountainCarEnvironment::getInstance();
  mce.applyAction(std::round(action[0]));
}

}
/* namespace AI */
