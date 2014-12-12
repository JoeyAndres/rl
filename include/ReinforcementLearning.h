/*
 * ReinforcementLearning.h
 *
 *  Created on: May 31, 2014
 *      Author: jandres
 */

#ifndef REINFORCEMENTLEARNING_H_
#define REINFORCEMENTLEARNING_H_

#include <cstdlib>
#include <set>
#include <map>
#include <iostream>
#include <shared_mutex>

#include "StateAction.h"
#include "LearningAlgorithm.h"
#include "Policy.h"
#include "StateActionPairContainer.h"

using namespace std;

namespace AI {
namespace Algorithm {
namespace RL {

/*! \class ReinforcementLearning
 *  \brief Abstract class for all Reinforcement learning algorithms.
 *  \tparam S state data type.
 *  \tparam A action data type.
 *
 * All reinforcement algorithm inherit from this class.
 */
template<class S, class A>
class ReinforcementLearning : public LearningAlgorithm<S, A> {
 public:
  /**
   * @param stepSize range \f$[0.0, 1.0]\f$. High step size means faster learning, but
   * less precise convergence.
   * @param discountRate range \f$[0.0, 1.0]\f$. High discount rate means more
   * consideration of future events.
   * @param policy online policy, that is policy used for action selection.
   */
  ReinforcementLearning(AI::FLOAT stepSize, AI::FLOAT discountRate,
                        Policy::Policy<S, A>& policy);

  /**
   * Returns the action that will most "likely" gives the highest reward from the
   * current state.
   * @param state the state to apply the argMax to.
   * @param stateAction map of StateAction to value.
   * @param actionSet a set of possible actions.
   * @return the action that will "likely" gives the highest reward.
   */
  A argMax(const S& state, const set<A>& actionSet) const;

  /**
   * @return current discount rate.
   */
  virtual AI::FLOAT getDiscountRate() const;

  /**
   * @param discountRate
   */
  virtual void setDiscountRate(AI::FLOAT discountRate);

  /**
   * @return current stepSize.
   */
  virtual AI::FLOAT getStepSize() const;

  /**
   * @param stepSize set the step size of Reinforcement Learning.
   */
  virtual void setStepSize(AI::FLOAT stepSize);

  /**
   * Does the main back up for all Temporal difference:
   * \f$ Q[S, A] \leftarrow Q[S, A] + \alpha\times [R + \gamma \times max_{A'}Q[S', A'] - Q[S, A] ]\f$
   * @param currentStateAction \f$(S, A)\f$, current state-action pair.
   * @param reward \f$R\f$, reward after \f$(S, A)\f$.
   * @param nextStateActionPair \f$(S', A')\f$, next state-action pair.
   */
  virtual void backUpStateActionPair(
      const StateAction<S, A>& currentStateAction, const AI::FLOAT reward,
      const StateAction<S, A>& nextStateActionPair);

  /**
   * Get Action with respect to learning/offline policy.
   * @param currentState state to acquire state-action values from.
   * @param actionSet Set of actions.
   * @return Action with respect to learning/offline policy.
   */
  A getLearningAction(const S& currentState, const set<A>& actionSet);

  /**
   * @param stateAction to acquire a value of.
   * @return the value of state-action pair.
   */
  virtual AI::FLOAT getStateActionValue(const StateAction<S, A>& stateAction);

  /**
   * \f$ Q[ S, A ] \leftarrow R \f$
   * @param stateAction to retrieve value from.
   * @param reward to set to the new state-action value.
   */
  virtual void setStateActionValue(const StateAction<S, A>& stateAction,
                                   const AI::FLOAT& reward);

  /**
   * @return state-action pair container.
   */
  const StateActionPairContainer<S, A>& getStateActionPairContainer() const;

  /**
   * @param stateActionPairContainer set state-action pair container.
   */
  void setStateActionPairContainer(
      const StateActionPairContainer<S, A>& stateActionPairContainer);

 public:
  // Inherited.

  virtual void update(const StateAction<S, A>& currentStateAction,
                      const S& nextState, const AI::FLOAT reward,
                      const set<A>& actionSet);
  virtual A getAction(const S& currentState, const set<A>& actionSet);

 protected:
  void _buildActionValueMap(const set<A>& actionSet, const S& currentState,
                            map<A, AI::FLOAT>& actionValueMap);
 protected:
  AI::FLOAT _stepSize;
  AI::FLOAT _discountRate;
  StateActionPairContainer<S, A> _stateActionPairContainer;

  mutable std::shared_timed_mutex _generalLock;  // General Lock.
  mutable std::shared_timed_mutex _containerLock;
  mutable std::shared_timed_mutex _stepSizeLock;
  mutable std::shared_timed_mutex _discountRateLock;
};

template<class S, class A>
ReinforcementLearning<S, A>::ReinforcementLearning(
    AI::FLOAT stepSize, AI::FLOAT discountRate, Policy::Policy<S, A>& policy)
    : LearningAlgorithm<S, A>(policy) {
  _stepSize = stepSize;
  _discountRate = discountRate;
}

template<class S, class A>
A ReinforcementLearning<S, A>::argMax(
    const S& state, const set<A>& actionSet) const {
  A greedAct = *(actionSet.begin());
  AI::FLOAT currentValue = this->_stateActionPairContainer[StateAction<S, A>(
      state, greedAct)];
  for (const A& action : actionSet) {
    AI::FLOAT value = this->_stateActionPairContainer[StateAction<S, A>(state,
                                                                        action)];
    if (currentValue < value) {
      currentValue = value;
      greedAct = action;
    }
  }
  return greedAct;
}

template<class S, class A>
inline AI::FLOAT ReinforcementLearning<S, A>::getDiscountRate() const {
  return _discountRate;
}

template<class S, class A>
inline void ReinforcementLearning<S, A>::setDiscountRate(
    AI::FLOAT discountRate) {
  _discountRate = discountRate;
}

template<class S, class A>
inline AI::FLOAT ReinforcementLearning<S, A>::getStepSize() const {
  return _stepSize;
}

template<class S, class A>
inline void ReinforcementLearning<S, A>::setStepSize(
    AI::FLOAT stepSize) {
  _stepSize = stepSize;
}

template<class S, class A>
inline const StateActionPairContainer<S, A>& ReinforcementLearning<
    S, A>::getStateActionPairContainer() const {
  return _stateActionPairContainer;
}

template<class S, class A>
inline void ReinforcementLearning<S, A>::setStateActionPairContainer(
    const StateActionPairContainer<S, A>& stateActionPairContainer) {
  _stateActionPairContainer = stateActionPairContainer;
}

template<class S, class A>
inline void ReinforcementLearning<S, A>::setStateActionValue(
    const StateAction<S, A>& stateAction, const AI::FLOAT& reward) {
  _stateActionPairContainer.setStateActionValue(stateAction, reward);
}

template<class S, class A>
inline A ReinforcementLearning<S, A>::getLearningAction(
    const S& currentState, const set<A>& actionSet) {
  _stateActionPairContainer.addState(currentState,
                                     this->_defaultStateActionValue, actionSet);
  map<A, AI::FLOAT> actionValueMap;
  _buildActionValueMap(actionSet, currentState, actionValueMap);
  return this->_getLearningPolicyAction(actionValueMap, actionSet);
}

template<class S, class A>
void ReinforcementLearning<S, A>::_buildActionValueMap(
    const set<A>& actionSet, const S& currentState,
    map<A, AI::FLOAT>& actionValueMap) {
  for (const A& action : actionSet) {
    actionValueMap[action] = _stateActionPairContainer[StateAction<S, A>(
        currentState, action)];
  }
}

template<class S, class A>
A ReinforcementLearning<S, A>::getAction(
    const S& currentState, const set<A>& actionSet) {
  _stateActionPairContainer.addState(currentState,
                                     this->_defaultStateActionValue, actionSet);
  map<A, AI::FLOAT> actionValueMap;
  _buildActionValueMap(actionSet, currentState, actionValueMap);
  return this->_controlPolicy->getAction(actionValueMap, actionSet);
}

template<class S, class A>
AI::FLOAT ReinforcementLearning<S, A>::getStateActionValue(
    const StateAction<S, A>& stateAction) {
  return _stateActionPairContainer.getStateActionValue(stateAction);
}

template<class S, class A>
void ReinforcementLearning<S, A>::backUpStateActionPair(
    const StateAction<S, A>& currentStateAction, const AI::FLOAT reward,
    const StateAction<S, A>& nextStateActionPair) {
  std::unique_lock < std::shared_timed_mutex > containerLock(_containerLock);

  // Next state-action value (nSAV) and current state-action value (cSAV).
  AI::FLOAT nSAV = getStateActionValue(nextStateActionPair);
  AI::FLOAT cSAV = getStateActionValue(currentStateAction);
  AI::FLOAT discountRate = this->_discountRate;

  setStateActionValue(
      currentStateAction,
      cSAV + this->_stepSize * (reward + discountRate * nSAV - cSAV));
}

template<class S, class A>
void ReinforcementLearning<S, A>::update(
    const StateAction<S, A>& currentStateAction, const S& nextState,
    const AI::FLOAT reward, const set<A>& actionSet) {
  (void) reward;
  _stateActionPairContainer.addState(currentStateAction.getState(),
                                     this->_defaultStateActionValue, actionSet);
  _stateActionPairContainer.addState(nextState, this->_defaultStateActionValue,
                                     actionSet);
}

} /* namespace RL */
} /* namespace Algorithm */
} /* namespace AI */

#endif /* REINFORCEMENTLEARNING_H_ */
