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

const rl::spState<rl::INT> A(new rl::INT(0)), B(new rl::INT(1)), C(new rl::INT(2)), D(new rl::INT(3)), T(new rl::INT(4));
const rl::spAction<rl::INT> L(new rl::INT(0)), R(new rl::INT(1));

namespace rl {

class RandomWalkEnvironment : public Environment<rl::INT, rl::INT>{
 public:
  enum State : int { A = 0, B, C, D, T };
  enum Action : int { L = 0, R };

 public:
  RandomWalkEnvironment(Actuator<rl::INT>& actuator, Sensor<rl::INT>& sensor);

  virtual std::pair<spState<INT>, FLOAT> getNextStateAndReward(const StateAction<rl::INT, rl::INT>& stateAction) override;

 protected:
  map<StateAction<rl::INT, rl::INT>, spState<rl::INT>> _env;
};

} /* namespace rl */

#endif /* RANDOMWALKENVIRONMENT_H_ */
