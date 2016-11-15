/*
 * SensorMountainCar.h
 *
 *  Created on: Jun 12, 2014
 *      Author: jandres
 */

#ifndef SENSORMOUNTAINCAR_H_
#define SENSORMOUNTAINCAR_H_

#include <vector>

#include "rl"

using namespace std;

namespace rl {
class SensorMountainCar final :    
      public Sensor<STATE_CONT> {
public:
  SensorMountainCar();
  virtual bool isTerminalState(const STATE_CONT& stateData) const;
};

} /* namespace rl */

#endif /* SENSORMOUNTAINCAR_H_ */
