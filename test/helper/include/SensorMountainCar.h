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
namespace agent {
class SensorMountainCar final :
  public Sensor<stateCont> {
 public:
  SensorMountainCar();
  virtual bool isTerminalState(const spStateCont &stateData) const;
};
}
} /* namespace rl */

#endif /* SENSORMOUNTAINCAR_H_ */
