/*
 * SensorMountainCar.h
 *
 *  Created on: Jun 12, 2014
 *      Author: jandres
 */

#ifndef SENSORMOUNTAINCAR_H_
#define SENSORMOUNTAINCAR_H_

#include <vector>

#include "SensorStatesContinous.h"

using namespace std;

namespace AI {
// TODO: Mkae SensorStatesContinous for Supervised Learners.
class SensorMountainCar final :
public SensorStatesContinous {
  virtual vector<AI::FLOAT> getSensorState();
  virtual bool isState(const vector<AI::FLOAT>& state) const;
  virtual AI::FLOAT getReward(vector<AI::FLOAT>& sensorState)
      throw (StateNotExistException);
  virtual bool isTerminalState(const vector<AI::FLOAT>& stateData) const;
};

} /* namespace AI */

#endif /* SENSORMOUNTAINCAR_H_ */
