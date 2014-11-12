/*
 * RandomWalkEnvironment.h
 *
 *  Created on: Jun 1, 2014
 *      Author: jandres
 */

#ifndef RANDOMWALKENVIRONMENT_H_
#define RANDOMWALKENVIRONMENT_H_

#include "GlobalHeader.h"

#include <map>

#include "StateAction.h"

using std::map;

const AI::INT A(0), B(1), C(2), D(3), T(4);
const AI::INT L(0), R(1);

namespace AI {

class RandomWalkEnvironment {
 private:
  RandomWalkEnvironment();
 public:
  static RandomWalkEnvironment& getInstance();

  void reset();

  void applyAction(AI::INT Action);
  AI::INT getCurrentState() const;
 private:
  AI::INT _currentState;
  map<AI::StateAction<AI::INT, AI::INT>, AI::INT> _env;
};

} /* namespace AI */

#endif /* RANDOMWALKENVIRONMENT_H_ */
