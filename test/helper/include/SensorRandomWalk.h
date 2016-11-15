/*
 * SensorRandomWalk.h
 *
 *  Created on: Jun 1, 2014
 *      Author: jandres
 */

#ifndef SENSORRANDOMWALK_H_
#define SENSORRANDOMWALK_H_

#include "rl"

namespace rl {

class  SensorRandomWalk : public SensorDiscrete<rl::INT> {
 public:
  SensorRandomWalk();
};

} /* namespace rl */

#endif /* SENSORRANDOMWALK_H_ */
