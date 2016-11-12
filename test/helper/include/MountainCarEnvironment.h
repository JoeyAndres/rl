/*
 * MountainCarEnvironment.h
 *
 *  Created on: Jun 12, 2014
 *      Author: jandres
 */

#ifndef MOUNTAINCARENVIRONMENT_H_
#define MOUNTAINCARENVIRONMENT_H_

#include "GlobalHeader.h"

#include <vector>

#include "Environment.h"

using namespace std;

#define POS 0
#define VEL 1

namespace AI {

class MountainCarEnvironment :
      public Environment<STATE_CONT, ACTION_CONT>{
 public:
  MountainCarEnvironment();

  // Overloaded methods.
  virtual const STATE_CONT& getLastObservedState() const;
  virtual AI::FLOAT getLastObservedReward() const;
  virtual AI::FLOAT applyAction(const ACTION_CONT& Action);
  virtual void reset();
  
 private:
  STATE_CONT _currentState;
  AI::FLOAT _currentReward;
};

} /* namespace AI */

#endif /* MOUNTAINCARENVIRONMENT_H_ */
