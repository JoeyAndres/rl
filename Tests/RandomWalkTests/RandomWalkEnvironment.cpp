/*
 * RandomWalkEnvironment.cpp
 *
 *  Created on: Jun 1, 2014
 *      Author: jandres
 */

#include "RandomWalkEnvironment.h"

namespace AI {

RandomWalkEnvironment::RandomWalkEnvironment() {
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

RandomWalkEnvironment& RandomWalkEnvironment::getInstance() {
  static RandomWalkEnvironment instance;
  return instance;
}

void RandomWalkEnvironment::applyAction(AI::INT Action) {
  _currentState = _env[StateAction<AI::INT, AI::INT>(_currentState, Action)];
}

AI::INT RandomWalkEnvironment::getCurrentState() const {
  return _currentState;
}

} /* namespace AI */
