/**
 * SensorMountainCar.cpp
 */

#include <vector>
#include <iostream>

#include "SensorMountainCar.h"
#include "MountainCarEnvironment.h"

using namespace std;

namespace AI {

SensorMountainCar::SensorMountainCar(Environment<STATE_CONT, ACTION_CONT>& env) :
    SensorBase<STATE_CONT, ACTION_CONT>(env) {
}

bool SensorMountainCar::isTerminalState(
    const STATE_CONT& stateData) const {
  if (abs(stateData[0] - 0.50F) <= 0.01F) {
    return true;
  }

  return false;
}

}

/* namespace AI */
