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

class MountainCarEnvironment : public Environment<stateCont, actionCont>{
 public:
  using SA = Environment<stateCont, actionCont>::SA;

 public:
  MountainCarEnvironment(Actuator<stateCont>& actuator, Sensor<stateCont>& sensor);

  // Overloaded methods.
  virtual rl::spStateAndReward<stateCont> getNextStateAndReward(const SA& stateAction) override;
};

} /* namespace rl */

#endif /* MOUNTAINCARENVIRONMENT_H_ */
