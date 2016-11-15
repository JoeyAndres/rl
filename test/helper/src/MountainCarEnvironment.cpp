/*
 * MountainCarEnvironment.cpp
 */

#include <cassert>
#include <cmath>
#include <iostream>

#include "../include/MountainCarEnvironment.h"

using namespace std;

namespace rl{

rl::MountainCarEnvironment::MountainCarEnvironment(
  Actuator<STATE_CONT>& actuator, Sensor<ACTION_CONT>& sensor) :
  rl::agent::Environment<STATE_CONT, ACTION_CONT>(actuator, sensor) {
}

std::pair<STATE_CONT, FLOAT> MountainCarEnvironment::getNextStateAndReward(
  const MountainCarEnvironment::SA& stateAction) {
  auto act = stateAction.getAction();

  /*if (act[0] < 0 || act[0] > 2) {
    cout << "Illegal" << endl;
    assert(false && "Action Set recognized.");
    }*/
  auto nextState = stateAction.getState();

  rl::INT copyAct = act[0] - 1;
  rl::FLOAT nextReward = -1;
  if (copyAct == 0) {
    nextReward = -1;
  } else {
    nextReward = -2;
  }

  nextState[VEL] +=
      (0.001F * copyAct - 0.0025F * cos(3.0F * nextState[POS]));

  if (nextState[VEL] < -0.07F)
    nextState[VEL] = -0.07F;
  else if (nextState[VEL] >= 0.07F)
    nextState[VEL] = 0.06999999F;
  nextState[POS] += nextState[VEL];
  if (nextState[POS] >= 0.5F) {
    nextState[POS] = 0.5;
    nextReward = 0;
  } else if (nextState[POS] < -1.2F) {
    nextState[POS] = -1.2F;
    nextState[VEL] = 0.0F;
  }


  return { nextState, nextReward };
}

} // rl
