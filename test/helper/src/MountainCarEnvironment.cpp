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
  Actuator<stateCont>& actuator, Sensor<actionCont>& sensor) :
  rl::agent::Environment<stateCont, actionCont>(actuator, sensor) {
}

rl::spStateAndReward<rl::stateCont> MountainCarEnvironment::getNextStateAndReward(
  const MountainCarEnvironment::SA& stateAction) {
  auto act = stateAction.getAction();

  /*if (act[0] < 0 || act[0] > 2) {
    cout << "Illegal" << endl;
    assert(false && "Action Set recognized.");
    }*/
  auto nextState = stateAction.getState();

  rl::INT copyAct = act->at(0) - 1;
  rl::FLOAT nextReward = -1;
  if (copyAct == 0) {
    nextReward = -1;
  } else {
    nextReward = -2;
  }

  nextState->at(VEL) +=
      (0.001F * copyAct - 0.0025F * cos(3.0F * nextState->at(POS)));

  if (nextState->at(VEL) < -0.07F)
    nextState->at(VEL) = -0.07F;
  else if (nextState->at(VEL) >= 0.07F)
    nextState->at(VEL) = 0.06999999F;
  nextState->at(POS) += nextState->at(VEL);
  if (nextState->at(POS) >= 0.5F) {
    nextState->at(POS) = 0.5;
    nextReward = 0;
  } else if (nextState->at(POS) < -1.2F) {
    nextState->at(POS) = -1.2F;
    nextState->at(VEL) = 0.0F;
  }


  return { nextState, nextReward };
}

} // rl
