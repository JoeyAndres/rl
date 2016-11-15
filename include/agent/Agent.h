/*
 * Agent.h
 *
 *  Created on: May 30, 2014
 *      Author: Joey Andres
 */

#pragma once

#include "../declares.h"

#include <vector>
#include <map>
#include <algorithm>
#include <cassert>
#include <iostream>

#include "../algorithm/LearningAlgorithm.h"
#include "Environment.h"
#include "StateAction.h"
#include "StateActionPairContainer.h"

using namespace std;

namespace rl {
namespace agent {

/*! \class AgentSupervised
 *  \brief A class that represent an rl agent for suprvised learning.
 *
 *  Supervised learning agent don't interact with the enivornment, but
 *  only takes data from the environment.
 *
 *  \tparam S State data type.
 *  \tparam A Action data type.
 */
template<class S, class A>
class AgentSupervised {
 public:
  /**
   * @param learningAlgorithm aggregate a Learning algorithm
   */
  AgentSupervised(
    ActionSet<A>& actionSet,
    algorithm::LearningAlgorithm<S, A>& learningAlgorithm) :
    _actionSet(actionSet),
    _learningAlgorithm(learningAlgorithm) {}

  /**
   * For training (instead of control) purposes.
   * @param state
   * @param action
   * @param reward
   * @param nextState
   */
  virtual void train(const S& state, const A& action, FLOAT reward, const S& nextState) {
    this->_learningAlgorithm.update(StateAction<S, A>(state, action),
                                    nextState,
                                    reward,
                                    this->_actionSet.getActionSet());
  }

 protected:
  ActionSet<A>& _actionSet;  //!< Aggregate an Actuator object.
  algorithm::LearningAlgorithm<S, A>& _learningAlgorithm;
};

/*! \class Agent
 *  \brief A class that represent an rl agent.
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
  Agent(Environment<S, A>& environment,
        algorithm::LearningAlgorithm<S, A>& learningAlgorithm);

  /**
   * For training (instead of control) purposes.
   * @param state
   * @param action
   * @param reward
   * @param nextState
   */
  virtual void train(const S& state, const A& action, FLOAT reward, const S& nextState);

  /**
   * Prepare agent prior to start execution.
   */
  virtual void preExecute();

  /**
   * Execute a single time step.
   */
  virtual void execute();

  /**
   * Execute many timesteps until end of episode.
   * @param maxIter maximum iteration.
   * @return number of iteration to acheive the task.
   * @throw MaxIterationException maximum iteration in an episode is hit.
   */
  virtual size_t executeEpisode(UINT maxIter=MAX_EPISODES);

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

  /**
   * @param action Agent applies action to the environment.
   */
  virtual void applyAction(const A& action);
  
  /**
   * @return CurrentState of the agent.
   */
  virtual S getLastObservedState() const;

  /**
   * Calls the Environment<S, A>::reset
   */
  virtual void reset();

 protected:
  /*! \var _learningAlgorithm
   *  Aggregates a learning algorithm.
   */
  algorithm::LearningAlgorithm<S, A>& _learningAlgorithm;

  Environment<S, A>& _environment;  // !< Aggregate environment obj.

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
 *
 *  TODO: Made by young me, probably under a lot of stress so above statement doesn't makes sense. Remove this crap.
 */
template<class D = FLOAT>
using AgentSL = Agent<vector<D>, vector<D>>;

template<class S, class A>
rl::agent::Agent<S, A>::Agent(Environment<S, A>& environment,
                       algorithm::LearningAlgorithm<S, A>& learningAlgorithm)
    : _environment(environment),
      _learningAlgorithm(learningAlgorithm),
      _accumulativeReward(0.0F) {
  _currentState = _environment.getSensor().getLastObservedState();
  _currentAction = _learningAlgorithm.getAction(
        _currentState, _environment.getActuator().getActionSet());
}

template<class S, class A>
S rl::agent::Agent<S, A>::getLastObservedState() const {
  return _environment.getSensor().getLastObservedState();
}

template<class S, class A>
void rl::agent::Agent<S, A>::train(const S& state, const A& action, FLOAT reward, const S& nextState) {
  this->_learningAlgorithm.update(
    StateAction<S, A>(state, action),
    nextState,
    reward,
    this->_environment.getActuator().getActionSet());
}

template<class S, class A>
void rl::agent::Agent<S, A>::preExecute() {
  _currentState = std::move(getLastObservedState());
  _currentAction = std::move(_learningAlgorithm.getAction(
        _currentState, _environment.getActuator().getActionSet()));
  _learningAlgorithm.reset();
  _accumulativeReward = 0.0F;
}

template<class S, class A>
void rl::agent::Agent<S, A>::execute() {
  // todo: Acquire last state and reward here.
  this->applyAction(_currentAction);
  S nextState = std::move(getLastObservedState());
  FLOAT reward = this->_environment.getSensor().getLastObservedReward();

  // Accumulate reward.
  this->_accumulativeReward += reward;

  // Update value, e.g. perform back ups.
  this->train(this->_currentState, this->_currentAction, reward, nextState);

  // Get the action from the algorithm.
  // Note the algorithm will retrieve from controlPolicy.
  this->_currentAction = std::move(this->_learningAlgorithm.getAction(
      nextState, this->_environment.getActuator().getActionSet()));

  // Update current state.
  this->_currentState = nextState;
}

template<class S, class A>
size_t rl::agent::Agent<S, A>::executeEpisode(UINT maxIter){
  preExecute();
  UINT i = 0;
  for(; i < maxIter && episodeDone() == false; i++) {
    execute();
  }
  postExecute();
  return i;
}

template<class S, class A>
bool rl::agent::Agent<S, A>::episodeDone() {
  return _environment.getSensor().isTerminalState(_currentState);
}

template<class S, class A>
rl::FLOAT rl::agent::Agent<S, A>::postExecute() {
  return _accumulativeReward;
}

template<class S, class A>
inline rl::FLOAT rl::agent::Agent<S, A>::getAccumulativeReward() const {
  return _accumulativeReward;
}

template<class S, class A>
void rl::agent::Agent<S, A>::applyAction(const A& action) {
  this->_environment.applyAction(action);
}

template<class S, class A>
void rl::agent::Agent<S, A>::reset() {
  this->_environment.reset();
};

}  // namespace agent
}  // namespace rl
