/*
 * RandomWalkEnvironment.h
 *
 *  Created on: Jun 1, 2014
 *      Author: jandres
 */

#ifndef RANDOMWALKENVIRONMENT_H_
#define RANDOMWALKENVIRONMENT_H_

#include <map>

#include "rl"

using std::map;

const rl::INT A(0), B(1), C(2), D(3), T(4);
const rl::INT L(0), R(1);

namespace rl {

class RandomWalkEnvironment : public Environment<rl::INT, rl::INT>{
 public:
  enum State : int { A = 0, B, C, D, T };
  enum Action : int { L = 0, R = 1 };

 public:
  RandomWalkEnvironment(Actuator<rl::INT>& actuator, Sensor<rl::INT>& sensor);

  virtual std::pair<INT, FLOAT> getNextStateAndReward(const StateAction<rl::INT, rl::INT>& stateAction) override;

 protected:
  map<StateAction<rl::INT, rl::INT>, FLOAT> _env;
};

} /* namespace rl */

#endif /* RANDOMWALKENVIRONMENT_H_ */
