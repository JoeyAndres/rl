/*
 * Agent.h
 *
 *  Created on: May 30, 2014
 *      Author: jandres
 *
 * TODO: Use template Specialization on Agent<S, A=AI::FLOAT/AI::INT/float/etc/etc>
 */

#ifndef AGENT_H_
#define AGENT_H_

#include "GlobalHeader.h"

#include <vector>
#include <map>
#include <algorithm>
#include <cassert>
#include <iostream>

#include "StateAction.h"
#include "LearningAlgorithm.h"
#include "SensorStatesAbstract.h"
#include "ActuatorAction.h"
#include "StateActionPairContainer.h"

using std::vector;
using std::map;
using std::cout;
using std::endl;

namespace AI {
/**
 * A class that represent an AI agent.
 */
template<class S, class A>
class Agent {
 public:
  /**
   * @param sensorInstance aggregate a sensor object.
   * @param actuatorInstance aggregate a actuator object.
   * @param learningAlgorithm aggregate a Learning algorithm
   */
  Agent(SensorStatesAbstract<S>& sensorInstance, Actuator<A>& actuatorInstance,
        Algorithm::LearningAlgorithm<S, A>& learningAlgorithm);

  /**
   * Prepare agent prior to start execution.
   */
  virtual void preExecute();

  /**
   * Execute a single time step.
   */
  virtual void execute();

  /**
   * @return true if done.
   */
  virtual bool episodeDone();

  /**
   * Does clean up stuff after reaching terminal state.
   * @return Cummulative reward.
   */
  virtual FLOAT postExecute();

  /**
   * @return Acquire the accumulated reward so far within the episode.
   */
  FLOAT getAccumulativeReward() const;

 private:
  /**
   * @return CurrentState.
   */
  S _getCurrentState();

 protected:
  // Aggregated learning algorithm.
  Algorithm::LearningAlgorithm<S, A>& _learningAlgorithm;

  SensorStatesAbstract<S>& _sensorInstance;  // Aggregate a Sensor object.
  Actuator<A>& _actuatorInstance;  // Aggregate an Actuator object.

  S _currentState;  // Keeps track of the current state.
  A _currentAction;  // Keeps track of the current action.

  // Keeps track of accumulation of reward during the span of the episode.
  // Specifically, after the call of preExecute, and after the call of postExecute.
  FLOAT _accumulativeReward;
};

template<class D = FLOAT>
using AgentSL = Agent<vector<D>, vector<D>>;

} /* namespace AI */

template<class S, class A>
AI::Agent<S, A>::Agent(SensorStatesAbstract<S>& sensorInstance,
                       Actuator<A>& actuatorInstance,
                       Algorithm::LearningAlgorithm<S, A>& learningAlgorithm)
    : _sensorInstance(sensorInstance),
      _actuatorInstance(actuatorInstance),
      _learningAlgorithm(learningAlgorithm),
      _accumulativeReward(0.0F) {
}

template<class S, class A>
S AI::Agent<S, A>::_getCurrentState() {
  S state = _sensorInstance.getSensorState();

  return state;
}

template<class S, class A>
void AI::Agent<S, A>::preExecute() {
  _currentState = _getCurrentState();
  _currentAction = _learningAlgorithm.getAction(
      _currentState, _actuatorInstance.getActionSet());
  _learningAlgorithm.reset();
  _accumulativeReward = 0.0F;
}

template<class S, class A>
void AI::Agent<S, A>::execute() {
  _actuatorInstance.applyAction(_currentAction);
  S nextState = _getCurrentState();
  FLOAT reward = _sensorInstance.getReward(_currentState);

  // Accumulate reward.
  _accumulativeReward += reward;

  // Update value, e.g. perform back ups.
  _learningAlgorithm.update(StateAction<S, A>(_currentState, _currentAction),
                            nextState, reward,
                            _actuatorInstance.getActionSet());

  // Get the action from the algorithm.
  // *Note the algorithm will retrieve from controlPolicy.
  _currentAction = _learningAlgorithm.getAction(
      nextState, _actuatorInstance.getActionSet());

  // Update current state.
  _currentState = nextState;
}

template<class S, class A>
bool AI::Agent<S, A>::episodeDone() {
  return _sensorInstance.isTerminalState(_currentState);
}

template<class S, class A>
AI::FLOAT AI::Agent<S, A>::postExecute() {
  return _accumulativeReward;
}

template<class S, class A>
inline AI::FLOAT AI::Agent<S, A>::getAccumulativeReward() const {
  return _accumulativeReward;
}

#endif /* AGENT_H_ */
