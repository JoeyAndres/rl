/*
 * LearningAlgorithm.h
 *
 *  Created on: May 31, 2014
 *      Author: jandres
 */

#pragma once

#include "GlobalHeader.h"

#include <map>
#include <set>
#include <memory>

#include "StateAction.h"
#include "EpsilonGreedy.h"

using std::set;
using std::map;

namespace AI {
namespace Algorithm {

/*! \class LearningAlgorithm
 *  \brief Base class for all learning algorithms.
 *
 *  All learning algorithm, reinforcement, supervised, unsupervised inherit from this class.
 *  \tparam S State Data type.
 *  \tparam A Action Data type.
 */
template<class S, class A>
class LearningAlgorithm {
 public:
  /**
   * @param controlPolicy policy for action selection online.
   */
  LearningAlgorithm(Policy::Policy<S, A>& controlPolicy);

  /**
   * Update the stateAction map.
   * @param currentState currentState agent is in.
   * @param currentAction action taken by agent by being in currentState.
   * @param nextState nextState by taking currentAction in currentState.
   * @param reward reward of currentStateAction.
   * @param actionSet A set of all actions.
   */
  virtual void update(const StateAction<S, A>& currentStateAction,
                      const S& nextState, const AI::FLOAT reward,
                      const set<A>& actionSet) = 0;

  /**
   * @param state the state to take the action to.
   * @param actionSet set of possible actions.
   * @return action based on control policy and current state.
   */
  virtual A getAction(const S& state, const set<A>& actionSet) = 0;

  /**
   * @param stateAction
   * @return Value of stateAction.
   */
  virtual AI::FLOAT getStateActionValue(
      const StateAction<S, A>& stateAction) = 0;

  /**
   * @param policy to set the current control policy with.
   */
  void setControltPolicy(Policy::Policy<S, A>& policy);

  /**
   * @return current control policy
   */
  Policy::Policy<S, A>& getControlPolicy();

  /**
   * Reset anything prior to running episode.
   */
  virtual void reset();

  /**
   * @return current default action value.
   */
  const AI::FLOAT& getDefaultStateActionValue() const;

  /**
   * @param defaultStateActionValue set the default state action value.
   */
  void setDefaultStateActionValue(const AI::FLOAT& defaultStateActionValue);

  /**
   * @param policy set the new learning policy.
   */
  void setLearningPolicy(Policy::Policy<S, A>& policy);

  /**
   * @return current learning policy.
   */
  const Policy::Policy<S, A> & getLearningPolicy() const;

 protected:
  /**
   * Returns the action selected by learning policy given action values from some state.
   * @param actionValueMap a mapping of action and their reward given current state.
   * @param actionSet current action set.
   * @return action selected by learning policy.
   */
    A _getLearningPolicyAction(const map<A, AI::FLOAT>& actionValueMap,
                                    const set<A>& actionSet);

 protected:
  AI::FLOAT _defaultStateActionValue;  //!< Place holder for default state action value.
  Policy::Policy<S, A>& _controlPolicy;  //!< Policy for action selection online.
  Policy::Policy<S, A>& _learningPolicy;  //!< Policy for action selection offline.

 protected:
  static Policy::EpsilonGreedy<S, A> _defaultLearningPolicy;  //!< Default offline policy.
};

template<class S, class A>
Policy::EpsilonGreedy<S, A> LearningAlgorithm<S, A>::_defaultLearningPolicy(
    AI::DEFAULT_GREEDINESS_LEARNING_POLICY);

template<class S, class A>
LearningAlgorithm<S, A>::LearningAlgorithm(Policy::Policy<S, A>& controlPolicy)
    : _controlPolicy(controlPolicy),
      _learningPolicy(_defaultLearningPolicy) {
  _defaultStateActionValue = AI::FLOAT();
}

template<class S, class A>
void LearningAlgorithm<S, A>::setControltPolicy(Policy::Policy<S, A>& policy) {
  this->_controlPolicy = policy;
}

template<class S, class A>
Policy::Policy<S, A>& LearningAlgorithm<S, A>::getControlPolicy() {
  return _controlPolicy;
}

template<class S, class A>
void LearningAlgorithm<S, A>::reset() {
}

template<class S, class A>
inline const AI::FLOAT& LearningAlgorithm<S, A>::getDefaultStateActionValue() const {
  return _defaultStateActionValue;
}

template<class S, class A>
inline void LearningAlgorithm<S, A>::setDefaultStateActionValue(
    const AI::FLOAT& defaultStateActionValue) {
  _defaultStateActionValue = defaultStateActionValue;
}
} /* namespace Algorithm */
} /* namespace AI */

template<class S, class A>
inline void AI::Algorithm::LearningAlgorithm<S, A>::setLearningPolicy(
    Policy::Policy<S, A>& policy) {
  _learningPolicy = policy;
}

template<class S, class A>
inline const AI::Algorithm::Policy::Policy<S, A>& AI::Algorithm::LearningAlgorithm<
    S, A>::getLearningPolicy() const {
  return _learningPolicy;
}

template<class S, class A>
inline A AI::Algorithm::LearningAlgorithm<S, A>::_getLearningPolicyAction(
    const map<A, AI::FLOAT>& actionValueMap, const set<A>& actionSet) {
  return _learningPolicy.getAction(actionValueMap, actionSet);
}
