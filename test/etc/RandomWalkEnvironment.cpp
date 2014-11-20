/*
 * RandomWalkEnvironment.cpp
 *
 *  Created on: Jun 1, 2014
 *      Author: jandres
 */

#include "RandomWalkEnvironment.h"

namespace AI {

RandomWalkEnvironment::RandomWalkEnvironment() :
    Environment<AI::INT, AI::INT>(){
  this->_currentState = B;
  _env[AI::StateAction<AI::INT, AI::INT>(A, L)] = T;
  _env[AI::StateAction<AI::INT, AI::INT>(A, R)] = B;
  _env[AI::StateAction<AI::INT, AI::INT>(B, L)] = A;
  _env[AI::StateAction<AI::INT, AI::INT>(B, R)] = C;
  _env[AI::StateAction<AI::INT, AI::INT>(C, L)] = B;
  _env[AI::StateAction<AI::INT, AI::INT>(C, R)] = D;
  _env[AI::StateAction<AI::INT, AI::INT>(D, L)] = C;
  _env[AI::StateAction<AI::INT, AI::INT>(D, R)] = T;
}

void RandomWalkEnvironment::reset() {
  _currentState = B;
}

AI::FLOAT RandomWalkEnvironment::applyAction(const AI::INT& Action) {
  _currentState = _env[StateAction<AI::INT, AI::INT>(_currentState, Action)];
  return getLastObservedReward();
}

const AI::INT& RandomWalkEnvironment::getLastObservedState() const {
  return _currentState;
}

AI::FLOAT RandomWalkEnvironment::getLastObservedReward() const{
  if (_currentState == T) {
    return 0;
  }
  return -1;  
}

} /* namespace AI */
