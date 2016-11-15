/**
 * SensorMountainCar.cpp
 */

#include <vector>
#include <iostream>
#include <cmath>

#include "../include/SensorMountainCar.h"
#include "../include/MountainCarEnvironment.h"

using namespace std;

namespace rl {

SensorMountainCar::SensorMountainCar() :
  Sensor<STATE_CONT>(STATE_CONT(2, 0)) {
}

bool SensorMountainCar::isTerminalState(
    const STATE_CONT& stateData) const {
  if (std::abs(stateData[0] - 0.50F) <= 0.01F) {
    return true;
  }

  return false;
}

}

/* namespace rl */
