/**
 * LFEnvironment.h
 */

#pragma once

#include "GlobalHeader.h"

#include "Environment.h"

namespace AI{

class LFEnvironment final: public Environment<STATE_CONT, ACTION_CONT>{
public:
  LFEnvironment();

  // Overriden from base class.
  virtual const STATE_CONT& getLastObservedState() const;
  virtual AI::FLOAT getLastObservedReward() const;
  virtual AI::FLOAT applyAction(const ACTION_CONT& Action);
  virtual void reset();
  
protected:
  /**
   * @return the current light sensor readings.
   */
  STATE_CONT _getSensorReadings() const;

  /**
   * @return last applied action.
   */
  ACTION_CONT _getLastAppliedAction() const;

  /**
   * @return true if the line following robot is off course.
   */
  bool _isOffCourse() const;
  
private:
  STATE_CONT _currentState;
  ACTION_CONT _currentAction;
  AI::FLOAT _currentReward;
};

}  // AI
