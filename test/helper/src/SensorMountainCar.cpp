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
namespace agent {
SensorMountainCar::SensorMountainCar() :
  Sensor<stateCont>(rl::spStateCont(new rl::stateCont({ 2, 0 }))) {
}

bool SensorMountainCar::isTerminalState(
  const spStateCont &stateData) const {
  if (std::abs(stateData->at(POS) - 0.50F) <= 0.01F) {
    return true;
  }

  return false;
}
}
}

/* namespace rl */
