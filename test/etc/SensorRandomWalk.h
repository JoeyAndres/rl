/*
 * SensorRandomWalk.h
 *
 *  Created on: Jun 1, 2014
 *      Author: jandres
 */

#ifndef SENSORRANDOMWALK_H_
#define SENSORRANDOMWALK_H_

#include "SensorDiscrete.h"

namespace AI {

class SensorRandomWalk final : public SensorDiscrete<AI::INT, AI::INT> {
 public:
  SensorRandomWalk(Environment<AI::INT, AI::INT>& env);
};
} /* namespace AI */

#endif /* SENSORRANDOMWALK_H_ */
