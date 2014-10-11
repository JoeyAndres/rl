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

AI::MountainCarEnvironment::MountainCarEnvironment() {
  _currentState = vector < AI::FLOAT > (2, 0);
  _currentReward = 0.0F;
}

AI::MountainCarEnvironment& AI::MountainCarEnvironment::getInstance() {
  static MountainCarEnvironment staticInstance;
  return staticInstance;
}

void AI::MountainCarEnvironment::reset() {
  _currentState[POS] = -0.4F;
  _currentState[VEL] = 0.0F;
  _currentReward = 0.0F;
}

AI::FLOAT AI::MountainCarEnvironment::applyAction(AI::INT act) {
  if (act < 0 || act > 2) {
    cout << "Illegal" << endl;
    assert(false && "Action Set recognized.");
  }

  act = act - 1;
  AI::FLOAT reward = -1;
  if (act == 0) {
    reward = -1;
  } else {
    reward = -2;
  }

  _currentState[VEL] +=
      (0.001F * act - 0.0025F * cos(3.0F * _currentState[POS]));

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

const vector<AI::FLOAT>& AI::MountainCarEnvironment::getCurrentState() const {
  return _currentState;
}

