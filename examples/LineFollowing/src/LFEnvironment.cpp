/**
 * LFEnvironment.cpp
 */

#include "LFEnvironment.h"

namespace AI{

LFEnvironment::LFEnvironment() : Environment<STATE_CONT, ACTION_CONT>(){
  _currentState = _getSensorReadings();
  
  AI::FLOAT applyAction(ACTION_CONT(0, 0));  // No movement.
  
  _currentAction = ACTION_CONT(0, 0);
  _currentReward = 0.0F;
}

const STATE_CONT& LFEnvironment::getLastObservedState() const{
  _currentState;
}

AI::FLOAT LFEnvironment::getLastObservedReward() const{
  _currentReward;
}

AI::FLOAT LFEnvironment::applyAction(const ACTION_CONT& Action){
  
}

void LFEnvironment::reset(){
  // Stop.
  // Beep and block till robot is in position.
}

STATE_CONT LFEnvironment::_getSensorReadings() const{
}

ACTION_CONT LFEnvironment::_getLastAppliedAction() const{
}

bool LFEnvironment::_isOffCourse() const{
}

}  // AI
