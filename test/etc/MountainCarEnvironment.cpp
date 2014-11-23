/*
 * MountainCarEnvironment.cpp
 *
 *  Created on: Jun 12, 2014
 *      Author: jandres
 */

#include <cassert>
#include <cmath>
#include <iostream>

#include "MountainCarEnvironment.h"

using namespace std;

namespace AI{

AI::MountainCarEnvironment::MountainCarEnvironment() :
    AI::Environment<STATE_CONT, ACTION_CONT>(){
  _currentState = STATE_CONT(2, 0);
  _currentReward = 0.0F;
}

void AI::MountainCarEnvironment::reset() {
  _currentState[POS] = -0.4F;
  _currentState[VEL] = 0.0F;
  _currentReward = 0.0F;
}

AI::FLOAT AI::MountainCarEnvironment::applyAction(const ACTION_CONT& act) {
  /*if (act[0] < 0 || act[0] > 2) {
    cout << "Illegal" << endl;
    assert(false && "Action Set recognized.");
    }*/

  AI::INT copyAct = act[0] - 1;
  AI::FLOAT reward = -1;
  if (copyAct == 0) {
    reward = -1;
  } else {
    reward = -2;
  }
  
  _currentState[VEL] +=
      (0.001F * copyAct - 0.0025F * cos(3.0F * _currentState[POS]));

  if (_currentState[VEL] < -0.07F)
    _currentState[VEL] = -0.07F;
  else if (_currentState[VEL] >= 0.07F)
    _currentState[VEL] = 0.06999999F;
  _currentState[POS] += _currentState[VEL];
  if (_currentState[POS] >= 0.5F) {
    _currentState[POS] = 0.5;
    _currentReward = 0;
    return 0;
  }
  if (_currentState[POS] < -1.2F) {
    _currentState[POS] = -1.2F;
    _currentState[VEL] = 0.0F;
  }

  _currentReward = reward;
  return reward;
}

const STATE_CONT& AI::MountainCarEnvironment::getLastObservedState() const {
  return _currentState;
}

AI::FLOAT AI::MountainCarEnvironment::getLastObservedReward() const{
  return _currentReward;
}

} // AI
