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

#include "ActuatorBase.h"
#include "StateAction.h"
#include "LearningAlgorithm.h"
#include "SensorBase.h"
#include "StateActionPairContainer.h"

using std::vector;
using std::map;
using std::cout;
using std::endl;

namespace AI {

/*! \class Agent
 *  \brief A class that represent an AI agent.
 *
 *  In Artificial Intelligence, Agent is the entity that recieves input from
 *  environment. In response, it outputs action to environment.
 *
 *  \tparam S State data type.
 *  \tparam A Action data type.
 */
template<class S, class A>
class Agent {
 public:
  /**
   * @param sensorInstance aggregate a sensor object.
   * @param actuatorInstance aggregate an actuator object.
   * @param learningAlgorithm aggregate a Learning algorithm
   */
  Agent(SensorBase<S, A>& sensorInstance, ActuatorBase<S, A>& actuatorInstance,
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
   * @return true if episode is done.
   */
  virtual bool episodeDone();

  /**
   * Does clean up routines after reaching terminal state.
   * @return Cummulative reward.
   */
  virtual FLOAT postExecute();

  /**
   * @return Acquire the accumulated reward so far within the episode.
   */
  FLOAT getAccumulativeReward() const;

 private:
  /**
   * @return CurrentState of the agent.
   */
  S _getCurrentState();

 protected:
  /*! \var _learningAlgorithm
   *  Aggregates a learning algorithm.
   */
  Algorithm::LearningAlgorithm<S, A>& _learningAlgorithm;

  SensorBase<S, A>& _sensorInstance;  //!< Aggregate a Sensor object.
  ActuatorBase<S, A>& _actuatorInstance;  //!< Aggregate an Actuator object.

  S _currentState;  //!< Keeps track of the current state.
  A _currentAction;  //!< Keeps track of the current action.

  FLOAT _accumulativeReward; //!< Keeps track of accumulation of reward during
                             //!< the span of the episode.Specifically, after
                             //!< the call of preExecute, and after the call of
                             //!< postExecute.
};

/*! \typedef AgentSL
 *  \brief Agent for Supervised Learning.
 *  \tparam D data type of Supervised Learning agent.
 *
 *  Supervised Learning usually deals with multi-dimension states and action,
 *  hence the specific typedef of Agent.
 */
template<class D = FLOAT>
using AgentSL = Agent<vector<D>, vector<D>>;

} /* namespace AI */

template<class S, class A>
AI::Agent<S, A>::Agent(SensorBase<S, A>& sensorInstance,
                       ActuatorBase<S, A>& actuatorInstance,
                       Algorithm::LearningAlgorithm<S, A>& learningAlgorithm)
    : _sensorInstance(sensorInstance),
      _actuatorInstance(actuatorInstance),
      _learningAlgorithm(learningAlgorithm),
      _accumulativeReward(0.0F) {

  _currentState = _sensorInstance.getSensorState();
  _currentAction = _learningAlgorithm.getAction(
        _currentState, _actuatorInstance.getActionSet());
}

template<class S, class A>
S AI::Agent<S, A>::_getCurrentState() {
  return _sensorInstance.getSensorState();;
}

template<class S, class A>
void AI::Agent<S, A>::preExecute() {
  _currentState = std::move(_getCurrentState());
  _currentAction = std::move(_learningAlgorithm.getAction(
        _currentState, _actuatorInstance.getActionSet()));
  _learningAlgorithm.reset();
  _accumulativeReward = 0.0F;
}

template<class S, class A>
void AI::Agent<S, A>::execute() {
  _actuatorInstance.applyAction(_currentAction);
  S nextState = std::move(_getCurrentState());
  FLOAT reward = _sensorInstance.getLastObservedReward();

  // Accumulate reward.
  _accumulativeReward += reward;

  // Update value, e.g. perform back ups.
  _learningAlgorithm.update(StateAction<S, A>(_currentState, _currentAction),
                            nextState, reward,
                            _actuatorInstance.getActionSet());

  // Get the action from the algorithm.
  // Note the algorithm will retrieve from controlPolicy.
  _currentAction = std::move(_learningAlgorithm.getAction(
      nextState, _actuatorInstance.getActionSet()));

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
