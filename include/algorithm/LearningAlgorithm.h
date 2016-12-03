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

#include <map>
#include <set>
#include <memory>
#include <string>

#include "../declares.h"
#include "../agent/StateAction.h"
#include "../policy/EpsilonGreedy.h"
#include "../policy/EpsilonGreedyFactory.h"

using std::set;
using std::map;

using rl::agent::StateAction;
using rl::policy::Policy;
using rl::policy::spPolicy;
using rl::policy::EpsilonGreedy;
using rl::policy::spEpsilonGreedy;
using rl::policy::EpsilonGreedyFactory;

namespace rl {
namespace algorithm {

/*! \class LearningAlgorithm
 *  \brief Base class for all learning algorithms.
 *
 *  All learning algorithm, reinforcement, supervised, unsupervised inherit
 *  from this class.
 *  \tparam S State Data type.
 *  \tparam A Action Data type.
 */
template<class S, class A>
class LearningAlgorithm {
 public:
  /**
   * @param controlPolicy policy for action selection online.
   */
  explicit LearningAlgorithm(const spPolicy<S, A>& controlPolicy);

  /**
   * Update the stateAction map.
   * @param currentStateAction Current state-action pair.
   * @param nextState Next state
   * @param reward Reward for the transition from current-state action to next state-action.
   */
  virtual void update(const StateAction<S, A>& currentStateAction,
                      const spState<S>& nextState,
                      const rl::FLOAT reward,
                      const spActionSet<A>& actionSet) = 0;

  /**
   * @param state the state to take the action to.
   * @param actionSet set of possible actions.
   * @return action based on control policy and current state.
   */
  virtual spAction<A> getAction(
    const spState<S>& state,
    const spActionSet<A>& actionSet) = 0;

  /**
   * @param stateAction
   * @return Value of stateAction.
   */
  virtual rl::FLOAT getStateActionValue(
      const StateAction<S, A>& stateAction) = 0;

  /**
   * @param policy to set the current control policy with.
   */
  void setControlPolicy(const spPolicy<S, A>& policy);

  /**
   * @return current control policy
   */
  const spPolicy<S, A>& getControlPolicy() const;
  spPolicy<S, A>& getControlPolicy();

  /**
   * Reset anything prior to running episode.
   */
  virtual void reset();

  /**
   * @return current default action value.
   */
  FLOAT getDefaultStateActionValue() const;

  /**
   * @param defaultStateActionValue set the default state action value.
   */
  void setDefaultStateActionValue(rl::FLOAT defaultStateActionValue);

  /**
   * @param policy set the new learning policy.
   */
  void setLearningPolicy(const spPolicy<S, A>& policy);

  /**
   * @return current learning policy.
   */
  const spPolicy<S, A> & getLearningPolicy() const;
  spPolicy<S, A> & getLearningPolicy();

  /**
   * @file
   */
  void serialize(const std::string& file);

  /**
   * @file
   */
  void deSerialize(const std::string& file);

 protected:
  /**
   * Returns the action selected by learning policy given action values from
   * some state.
   * @param actionValueMap a mapping of action and their reward given current
   *                       state.
   * @param actionSet current action set.
   * @return action selected by learning policy.
   */
  spAction<A> _getLearningPolicyAction(
    const spActionValueMap<A>& actionValueMap,
    const spActionSet<A>& actionSet);

  /**
   * Returns the action selected by learning policy given action values from
   * some state.
   * @param actionValueMap a mapping of action and their reward given current state.
   * @param actionSet current action set.
   * @param maxAction action with maximum value.
   *                  (For optimization reason so it's not recalculated).
   * @return action selected by learning policy.
   */
  spAction<A> _getLearningPolicyAction(
    const spActionValueMap<A>& actionValueMap,
    const spActionSet<A>& actionSet,
    const spAction<A>& maxAction);

 protected:
  /*! \var _defaultStateActionValue
   *
   * Place holder for default state action value.
   */
  rl::FLOAT _defaultStateActionValue;

  /*! \var _controlPolicy
   *
   * Policy for action selection online.
   */
  spPolicy<S, A> _controlPolicy;

  /*! \var _learningPolicy
   *
   * Policy for action selection offline.
   */
  spPolicy<S, A> _learningPolicy;

 protected:
  /*! \var _defaultLearningPolicy
   *  \static
   *
   * Default offline policy.
   */
  static spPolicy<S, A> _defaultLearningPolicy;
};

template<class S, class A>
using spLearningAlgorithm = shared_ptr<LearningAlgorithm<S, A>>;

template<class S, class A>
spPolicy<S, A> LearningAlgorithm<S, A>::_defaultLearningPolicy =
  EpsilonGreedyFactory<S, A>(rl::DEFAULT_GREEDINESS_LEARNING_POLICY).get();

template<class S, class A>
LearningAlgorithm<S, A>::LearningAlgorithm(const spPolicy<S, A>& controlPolicy)
    : _controlPolicy(controlPolicy),
      _learningPolicy(_defaultLearningPolicy) {
  _defaultStateActionValue = rl::FLOAT();
}

template<class S, class A>
void LearningAlgorithm<S, A>::setControlPolicy(const spPolicy<S, A>& policy) {
  this->_controlPolicy = policy;
}

template<class S, class A>
const spPolicy<S, A>& LearningAlgorithm<S, A>::getControlPolicy() const {
  return _controlPolicy;
}

template<class S, class A>
spPolicy<S, A>& LearningAlgorithm<S, A>::getControlPolicy() {
  return _controlPolicy;
}

template<class S, class A>
void LearningAlgorithm<S, A>::reset() {
}

template<class S, class A>
rl::FLOAT LearningAlgorithm<S, A>::getDefaultStateActionValue() const {
  return _defaultStateActionValue;
}

template<class S, class A>
void LearningAlgorithm<S, A>::setDefaultStateActionValue(
    rl::FLOAT defaultStateActionValue) {
  _defaultStateActionValue = defaultStateActionValue;
}

template<class S, class A>
void LearningAlgorithm<S, A>::setLearningPolicy(
    const spPolicy<S, A>& policy) {
  this->_learningPolicy = policy;
}

template<class S, class A>
const spPolicy<S, A>& LearningAlgorithm<S, A>::getLearningPolicy() const {
  return _learningPolicy;
}

template<class S, class A>
spPolicy<S, A>& LearningAlgorithm<S, A>::getLearningPolicy() {
  return _learningPolicy;
}

template<class S, class A>
spAction<A> LearningAlgorithm<S, A>::_getLearningPolicyAction(
  const spActionValueMap<A>& actionValueMap,
  const spActionSet<A>& actionSet) {
  return _learningPolicy->getAction(actionValueMap, actionSet);
}

template<class S, class A>
spAction<A> LearningAlgorithm<S, A>::_getLearningPolicyAction(
  const spActionValueMap<A>& actionValueMap,
  const spActionSet<A>& actionSet,
  const spAction<A>& maxAction) {
  return _learningPolicy->getAction(actionValueMap, actionSet, maxAction);
}

template<class S, class A>
void LearningAlgorithm<S, A>::serialize(const std::string& file) {
}

template<class S, class A>
void LearningAlgorithm<S, A>::deSerialize(const std::string& file) {
}

}  // namespace algorithm
}  // namespace rl
