/*
 * ActuatorMountainCar.h
 *
 *  Created on: Jun 12, 2014
 *      Author: jandres
 */

#ifndef ACTUATORMOUNTAINCAR_H_
#define ACTUATORMOUNTAINCAR_H_

#include "GlobalHeader.h"

#include <vector>
#include <set>

#include "ActuatorAction.h"

using namespace std;

namespace AI {
class ActuatorMountainCar final : public Actuator<ACTION_CONT> {
 public:
  ActuatorMountainCar();
  ActuatorMountainCar(set<ACTION_CONT> actionSet);
  virtual void applyAction(const ACTION_CONT& action);
};

} /* namespace AI */

#endif /* ACTUATORMOUNTAINCAR_H_ */
