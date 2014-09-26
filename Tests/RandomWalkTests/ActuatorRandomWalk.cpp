/*
 * ActuatorRandomWalk.cpp
 *
 *  Created on: Jun 1, 2014
 *      Author: jandres
 */

#include "ActuatorRandomWalk.h"
#include "RandomWalkEnvironment.h"

namespace AI {

  void AI::ActuatorRandomWalk<AI::INT>::applyAction(const AI::INT& action) {
	RandomWalkEnvironment& rwe = RandomWalkEnvironment::getInstance();
	rwe.applyAction(action);
  }

} /* namespace AI */
