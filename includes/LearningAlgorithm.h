/*
 * SearchAlgorithm.h
 *
 *  Created on: May 31, 2014
 *      Author: jandres
 */

#ifndef SEARCHALGORITHM_H_
#define SEARCHALGORITHM_H_

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
  LearningAlgorithm(Policy<S, A>& controlPolicy);

  /**
   * Update the stateAction map.
   * @param currentState
   * @param currentAction
   * @param nextState
   * @param reward reward of currentState and currentAction.
   * @param stateAction A map of StateAction to Value.
   * @param actionSet A set of all actions.
   * @return next action to be executed.
   */
  virtual void update(const StateAction<S, A>& currentStateAction,
                      const S& nextState, const AI::FLOAT reward,
                      const set<A>& actionSet) = 0;

  /**
   * A policy that varies between algorithms.
   */
  virtual const A& getAction(const S& state, const set<A>& actionSet) = 0;

  /**
   * Acquire the value of the state action pair. Each algorithm group (rl,
   * supervised, unsupervised), or specific algorithm (Q, Sarsa, Gradient Descent)
   * must implement.
   * @param stateAction
   * @return Value of stateAction.
   */
  virtual AI::FLOAT getStateActionValue(
      const StateAction<S, A>& stateAction) = 0;

  /**
   * @param policy to set the current control policy with.
   */
  void seControltPolicy(Policy<S, A>& policy);

  /**
   * @return current control policy
   */
  Policy<S, A>& getControlPolicy();

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
  void setLearningPolicy(Policy<S, A>& policy);

  /**
   * @return current learning policy.
   */
  const Policy<S, A> & getLearningPolicy() const;

 protected:
  /**
   * Returns the action selected by learning policy given action values from some state.
   * @param actionValueMap a mapping of action and their reward given current state.
   * @param actionSet current action set.
   * @return action selected by learning policy.
   */
  const A& _getLearningPolicyAction(const map<A, AI::FLOAT>& actionValueMap,
                                    const set<A>& actionSet);

 protected:
  AI::FLOAT _defaultStateActionValue;  //!< Place holder for default state action value.
  Policy<S, A>& _controlPolicy;  //!< Policy for action selection online.
  Policy<S, A>& _learningPolicy;  //!< Policy for action selection offline.

 protected:
  static EpsilonGreedy<S, A> _defaultLearningPolicy;  //!< Default offline policy.
};

template<class S, class A>
EpsilonGreedy<S, A> LearningAlgorithm<S, A>::_defaultLearningPolicy(
    AI::DEFAULT_GREEDINESS_LEARNING_POLICY);

template<class S, class A>
LearningAlgorithm<S, A>::LearningAlgorithm(Policy<S, A>& controlPolicy)
    : _controlPolicy(controlPolicy),
      _learningPolicy(_defaultLearningPolicy) {
  _defaultStateActionValue = AI::FLOAT();
}

template<class S, class A>
void LearningAlgorithm<S, A>::seControltPolicy(Policy<S, A>& policy) {
  this->_controlPolicy = policy;
}

template<class S, class A>
Policy<S, A>& LearningAlgorithm<S, A>::getControlPolicy() {
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
    Policy<S, A>& policy) {
  _learningPolicy = policy;
}

template<class S, class A>
inline const AI::Algorithm::Policy<S, A>& AI::Algorithm::LearningAlgorithm<S, A>::getLearningPolicy() const {
  return _learningPolicy;
}

template<class S, class A>
inline const A& AI::Algorithm::LearningAlgorithm<S, A>::_getLearningPolicyAction(
    const map<A, AI::FLOAT>& actionValueMap, const set<A>& actionSet) {
  return _learningPolicy.getAction(actionValueMap, actionSet);
}

#endif /* SEARCHALGORITHM_H_ */
