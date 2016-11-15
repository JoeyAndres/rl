/*
 * MountainCarEnvironment.h
 *
 *  Created on: Jun 12, 2014
 *      Author: jandres
 */

#ifndef MOUNTAINCARENVIRONMENT_H_
#define MOUNTAINCARENVIRONMENT_H_

#include <vector>
#include <utility>

#include "rl"

using namespace std;

#define POS 0
#define VEL 1

namespace rl {

class MountainCarEnvironment : public Environment<STATE_CONT, ACTION_CONT>{
 public:
  using SA = Environment<STATE_CONT, ACTION_CONT>::SA;

 public:
  MountainCarEnvironment(Actuator<STATE_CONT>& actuator, Sensor<STATE_CONT>& sensor);

  // Overloaded methods.
  virtual std::pair<STATE_CONT, FLOAT> getNextStateAndReward(const SA& stateAction) override;
};

} /* namespace rl */

#endif /* MOUNTAINCARENVIRONMENT_H_ */
