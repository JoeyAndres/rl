/*
 * SensorMountainCar.h
 *
 *  Created on: Jun 12, 2014
 *      Author: jandres
 */

#ifndef SENSORMOUNTAINCAR_H_
#define SENSORMOUNTAINCAR_H_

#include "declares.h"

#include <vector>

#include "SensorBase.h"
#include "Environment.h"

using namespace std;

namespace AI {
class SensorMountainCar final :    
      public SensorBase<STATE_CONT, ACTION_CONT> {
public:
  SensorMountainCar(Environment<STATE_CONT, ACTION_CONT>& env);
  virtual bool isTerminalState(const STATE_CONT& stateData) const;
};

} /* namespace AI */

#endif /* SENSORMOUNTAINCAR_H_ */
