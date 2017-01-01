/**
 * rl - Reinforcement Learning
 * Copyright (C) 2016  Joey Andres<yeojserdna@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>

#include "../declares.h"
#include "../algorithm/LearningAlgorithm.h"
#include "Environment.h"
#include "StateAction.h"
#include "StateActionPairContainer.h"

using std::vector;

using rl::algorithm::spLearningAlgorithm;

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
    const spActionContainer<A>& actionContainer,
    const spLearningAlgorithm<S, A>& learningAlgorithm) :
    _actionContainer(actionContainer),
    _learningAlgorithm(learningAlgorithm) {}

  /**
   * For training (instead of control) purposes.
   * @param state
   * @param action
   * @param reward
   * @param nextState
   */
  virtual void train(const spState<S>& state,
                     const spAction<A>& action,
                     FLOAT reward,
                     const spState<S>& nextState) {
    this->_learningAlgorithm->update(
      StateAction<S, A>(state, action),
      nextState,
      reward,
      this->_actionContainer->getActionSet());
  }

 protected:
  spActionContainer<A> _actionContainer;  //!< Aggregate an Actuator object.
  spLearningAlgorithm<S, A> _learningAlgorithm;
};

/*! \class AgentSupervisedGD
 *  \brief AgentSupervised for Gradient Descent.
 *  \tparam D Number of dimension.
 *  \tparam STATE_DIM Number of state dimension.
 */
template<size_t D, size_t STATE_DIM = D-1>
using AgentSupervisedGD =
AgentSupervised<floatArray<STATE_DIM>, floatArray<D - STATE_DIM>>;

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
  Agent(const spEnvironment<S, A>& environment,
        const spLearningAlgorithm<S, A>& learningAlgorithm);

  /**
   * For training (instead of control) purposes.
   * @param state
   * @param action
   * @param reward
   * @param nextState
   */
  virtual void train(const spState<S>& state,
                     const spAction<A>& action,
                     FLOAT reward,
                     const spState<S>& nextState);

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
  virtual size_t executeEpisode(UINT maxIter = MAX_EPISODES);

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
  virtual void applyAction(const spAction<A>& action);

  /**
   * @return CurrentState of the agent.
   */
  virtual spState<S> getLastObservedState() const;

  /**
   * Calls the Environment<S, A>::reset
   */
  virtual void reset();

  /**
   * @return Last action applied.
   */
  spAction<A> getLastActionApplied() const;

 protected:
  /*! \var _learningAlgorithm
   *  Aggregates a learning algorithm.
   */
  spLearningAlgorithm<S, A> _learningAlgorithm;

  spEnvironment<S, A> _environment;  //!< Aggregate environment obj.

  spState<S> _currentState;  //!< Keeps track of the current state.
  spAction<A> _currentAction;  //!< Keeps track of the current action.

  FLOAT _accumulativeReward;  //!< Keeps track of accumulation of reward during
                              //!< the span of the episode.Specifically, after
                              //!< the call of preExecute, and after the call of
                              //!< postExecute.
};

/*! \class AgentGD
 *  \brief Agent for Gradient Descent.
 *  \tparam D Number of dimension.
 *  \tparam STATE_DIM Number of state dimension.
 */
template<size_t D, size_t STATE_DIM = D-1>
using AgentGD = Agent<floatArray<STATE_DIM>, floatArray<D - STATE_DIM>>;

template<class S, class A>
Agent<S, A>::Agent(const spEnvironment<S, A>& environment,
                   const spLearningAlgorithm<S, A>& learningAlgorithm)
  : _environment(environment),
    _learningAlgorithm(learningAlgorithm),
    _accumulativeReward(0.0F) {
  _currentState = _environment->getSensor()->getLastObservedState();
  _currentAction = _learningAlgorithm->getAction(
        _currentState, _environment->getActuator()->getActionSet());
}

template<class S, class A>
spState<S> Agent<S, A>::getLastObservedState() const {
  return _environment->getSensor()->getLastObservedState();
}

template<class S, class A>
void Agent<S, A>::train(
  const spState<S>& state,
  const spAction<A>& action,
  FLOAT reward,
  const spState<S>& nextState) {
  this->_learningAlgorithm->update(
    StateAction<S, A>(state, action),
    nextState,
    reward,
    this->_environment->getActuator()->getActionSet());
  // TODO(jandres): If environment is known, allow actuator actions to be
  //                state dependent.
}

template<class S, class A>
void Agent<S, A>::preExecute() {
  _learningAlgorithm->reset();
  _currentState = std::move(getLastObservedState());
  _currentAction = std::move(_learningAlgorithm->getAction(
        _currentState, _environment->getActuator()->getActionSet()));
  _accumulativeReward = 0.0F;
}

template<class S, class A>
void Agent<S, A>::execute() {
  // todo(jandres): Acquire last state and reward here.
  this->applyAction(_currentAction);
  spState<S> nextState = std::move(getLastObservedState());
  FLOAT reward = this->_environment->getSensor()->getLastObservedReward();

  // Accumulate reward.
  this->_accumulativeReward += reward;

  // Update value, e.g. perform back ups.
  this->train(this->_currentState, this->_currentAction, reward, nextState);

  // Get the action from the algorithm.
  // Note the algorithm will retrieve from controlPolicy.
  this->_currentAction = std::move(this->_learningAlgorithm->getAction(
      nextState, this->_environment->getActuator()->getActionSet()));

  // Update current state.
  this->_currentState = nextState;
}

template<class S, class A>
size_t Agent<S, A>::executeEpisode(UINT maxIter) {
  preExecute();
  UINT i = 0;
  for (; i < maxIter && episodeDone() == false; i++) {
    execute();
    std::cout << "iter: " << i << std::endl;
  }
  postExecute();
  return i;
}

template<class S, class A>
bool Agent<S, A>::episodeDone() {
  return _environment->getSensor()->isTerminalState(_currentState);
}

template<class S, class A>
rl::FLOAT Agent<S, A>::postExecute() {
  return _accumulativeReward;
}

template<class S, class A>
inline rl::FLOAT Agent<S, A>::getAccumulativeReward() const {
  return _accumulativeReward;
}

template<class S, class A>
void Agent<S, A>::applyAction(const spAction<A>& action) {
  this->_environment->applyAction(action);
}

template<class S, class A>
void Agent<S, A>::reset() {
  this->_environment->reset();
}

template<class S, class A>
spAction<A> Agent<S, A>::getLastActionApplied() const {
  return _currentAction;
}

}  // namespace agent
}  // namespace rl
