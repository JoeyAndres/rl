/*
 * SensorStatesContinous.h
 *
 *  Created on: Jun 17, 2014
 *      Author: jandres
 */

#ifndef SENSORSTATESCONTINOUS_H_
#define SENSORSTATESCONTINOUS_H_

#include "GlobalHeader.h"

#include "SensorBase.h"

namespace AI {

/*! \class SensorContinous
 *  \brief Base class for sensor with continuous data.
 *
 *  Base class for sensor with continuous data(s).
 */
class SensorContinuous : public SensorBase<STATE_CONT > {
  virtual STATE_CONT getSensorState() = 0;
  virtual bool isState(const STATE_CONT& state) const = 0;
  virtual bool isTerminalState(const STATE_CONT& stateData) const = 0;

  /**
   * Maps sensorState to its corresponding reward.
   * @param sensorState to be mapped to its corresponding reward.
   * @return reward
   */
  virtual AI::FLOAT getReward(STATE_CONT& sensorState)
      throw (StateNotExistException) = 0;
};

} /* namespace AI */

#endif /* SENSORSTATESCONTINOUS_H_ */
