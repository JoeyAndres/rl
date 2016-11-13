/*
 * RandomWalkEnvironment.h
 *
 *  Created on: Jun 1, 2014
 *      Author: jandres
 */

#ifndef RANDOMWALKENVIRONMENT_H_
#define RANDOMWALKENVIRONMENT_H_

#include "declares.h"

#include <map>

#include "StateAction.h"
#include "Environment.h"

using std::map;

const AI::INT A(0), B(1), C(2), D(3), T(4);
const AI::INT L(0), R(1);

namespace AI {

class RandomWalkEnvironment : public Environment<AI::INT, AI::INT>{
 public:
  RandomWalkEnvironment();

  // Overloaded methods.
  const AI::INT& getLastObservedState() const;
  AI::FLOAT getLastObservedReward() const;
  AI::FLOAT applyAction(const AI::INT& Action);
  virtual void reset();
  
 private:
  AI::INT _currentState;
  map<AI::StateAction<AI::INT, AI::INT>, AI::INT> _env;
};

} /* namespace AI */

#endif /* RANDOMWALKENVIRONMENT_H_ */
