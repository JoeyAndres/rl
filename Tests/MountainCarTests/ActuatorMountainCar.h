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

#include "ActuatorAction.h"

using namespace std;

namespace AI {
class ActuatorMountainCar final : public Actuator<vector<AI::FLOAT> > {
public:
	virtual void applyAction(const vector<AI::FLOAT>& action);
};

} /* namespace AI */

#endif /* ACTUATORMOUNTAINCAR_H_ */
