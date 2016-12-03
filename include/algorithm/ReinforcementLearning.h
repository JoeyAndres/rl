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

#include <cstdlib>
#include <iostream>

#include "../agent/StateAction.h"
#include "../policy/Policy.h"
#include "../agent/StateActionPairContainer.h"
#include "LearningAlgorithm.h"

using rl::agent::StateActionPairContainer;
using rl::agent::StateActionNotExistException;
using rl::policy::Policy;
using rl::policy::spPolicy;

namespace rl {

namespace algorithm {

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
  ReinforcementLearning(rl::FLOAT stepSize,
                        rl::FLOAT discountRate,
                        const spPolicy<S, A>& policy);

  /**
   * Returns the action that will most "likely" gives the highest reward from the
   * current state.
   * @param state the state to apply the argMax to.
   * @param stateAction map of StateAction to value.
   * @param actionSet a set of possible actions.
   * @return the action that will "likely" gives the highest reward.
   */
  spAction<A> argMax(
    const spState<S>& state, const spActionSet<A>& actionSet) const;

  /**
   * @return current discount rate.
   */
  virtual rl::FLOAT getDiscountRate() const;

  /**
   * @param discountRate
   */
  virtual void setDiscountRate(rl::FLOAT discountRate);

  /**
   * @return current stepSize.
   */
  virtual rl::FLOAT getStepSize() const;

  /**
   * @param stepSize set the step size of Reinforcement Learning.
   */
  virtual void setStepSize(rl::FLOAT stepSize);

  /**
   * Does the main back up for all Temporal difference:
   * \f$ Q[S, A] \leftarrow Q[S, A] + \alpha\times [R + \gamma \times max_{A'}Q[S', A'] - Q[S, A] ]\f$
   * @param currentStateAction \f$(S, A)\f$, current state-action pair.
   * @param reward \f$R\f$, reward after \f$(S, A)\f$.
   * @param nextStateActionPair \f$(S', A')\f$, next state-action pair.
   */
  virtual void backUpStateActionPair(
      const StateAction<S, A>& currentStateAction, const rl::FLOAT reward,
      const StateAction<S, A>& nextStateActionPair);

  /**
   * Get Action with respect to learning/offline policy.
   * @param currentState state to acquire state-action values from.
   * @param actionSet Set of actions.
   * @return Action with respect to learning/offline policy.
   */
  spAction<A> getLearningAction(
    const spState<S>& currentState, const spActionSet<A>& actionSet);

  /**
   * @param stateAction to acquire a value of.
   * @return the value of state-action pair.
   */
  virtual rl::FLOAT getStateActionValue(const StateAction<S, A>& stateAction);

  /**
   * \f$ Q[ S, A ] \leftarrow R \f$
   * @param stateAction to retrieve value from.
   * @param reward to set to the new state-action value.
   */
  virtual void setStateActionValue(const StateAction<S, A>& stateAction,
                                   const rl::FLOAT& reward);

  /**
   * @return state-action pair container.
   */
  const StateActionPairContainer<S, A>& getStateActionPairContainer() const;
  StateActionPairContainer<S, A>& getStateActionPairContainer();

  /**
   * @param stateActionPairContainer set state-action pair container.
   */
  void setStateActionPairContainer(
      const StateActionPairContainer<S, A>& stateActionPairContainer);

 public:
  virtual void updateStateAction(const StateAction <S, A> &currentStateAction,
                                 const StateAction <S, A> &nextStateAction,
                                 const rl::FLOAT reward);
  virtual spAction<A> getAction(
    const spState<S>& currentState, const spActionSet<A>& actionSet);

 protected:
  spActionValueMap<A> _buildActionValueMap(
    const spActionSet<A>& actionSet,
    const spState<S>& currentState) const;

 protected:
  rl::FLOAT _stepSize;
  rl::FLOAT _discountRate;
  StateActionPairContainer<S, A> _stateActionPairContainer;
};

template<class S, class A>
std::ostream& operator<<(
  std::ostream& os, const ReinforcementLearning<S, A>& rl) {
  auto stateActionPairContainer = rl.getStateActionPairContainer();
  os << "{" << std::endl;
  for (auto iter = stateActionPairContainer.begin();
       iter != stateActionPairContainer.end();
       iter++) {
    os << "\t("
       << iter->first.getState()
       << ", " << iter->first.getAction()
       << "): " << iter->second
       << "," << std::endl;
  }
  os << "}" << std::endl;

  return os;
}

template<class S, class A>
ReinforcementLearning<S, A>::ReinforcementLearning(
    rl::FLOAT stepSize,
    rl::FLOAT discountRate,
    const spPolicy<S, A>& policy)
    : LearningAlgorithm<S, A>(policy) {
  _stepSize = stepSize;
  _discountRate = discountRate;
}

template<class S, class A>
spAction<A> ReinforcementLearning<S, A>::argMax(
    const spState<S>& state, const spActionSet<A>& actionSet) const {
  spAction<A> greedAct = *(actionSet.begin());

  rl::FLOAT currentValue = this->_defaultStateActionValue;
  try {
    currentValue =
      this->_stateActionPairContainer[StateAction<S, A>(state, greedAct)];
  } catch (StateActionNotExistException& e) {
    // Do nothing. We already assign it the default state-action value.
  }

  for (const spState<A>& action : actionSet) {
    rl::FLOAT value = this->_defaultStateActionValue;
    try {
      value = this->_stateActionPairContainer[StateAction<S, A>(state, action)];
    } catch (StateActionNotExistException& e) {
      // Do nothing. We already assign it the default state-action value.
    }

    if (currentValue < value) {
      currentValue = value;
      greedAct = action;
    }
  }
  return greedAct;
}

template<class S, class A>
rl::FLOAT ReinforcementLearning<S, A>::getDiscountRate() const {
  return _discountRate;
}

template<class S, class A>
void ReinforcementLearning<S, A>::setDiscountRate(
    rl::FLOAT discountRate) {
  _discountRate = discountRate;
}

template<class S, class A>
rl::FLOAT ReinforcementLearning<S, A>::getStepSize() const {
  return _stepSize;
}

template<class S, class A>
void ReinforcementLearning<S, A>::setStepSize(
    rl::FLOAT stepSize) {
  _stepSize = stepSize;
}

template<class S, class A>
const StateActionPairContainer<S, A>& ReinforcementLearning<
    S, A>::getStateActionPairContainer() const {
  return _stateActionPairContainer;
}

template<class S, class A>
StateActionPairContainer<S, A>& ReinforcementLearning<
  S, A>::getStateActionPairContainer() {
  return _stateActionPairContainer;
}

template<class S, class A>
void ReinforcementLearning<S, A>::setStateActionPairContainer(
    const StateActionPairContainer<S, A>& stateActionPairContainer) {
  _stateActionPairContainer = stateActionPairContainer;
}

template<class S, class A>
void ReinforcementLearning<S, A>::setStateActionValue(
    const StateAction<S, A>& stateAction, const rl::FLOAT& reward) {
  _stateActionPairContainer.setStateActionValue(stateAction, reward);
}

template<class S, class A>
spAction<A> ReinforcementLearning<S, A>::getLearningAction(
    const spState<S>& currentState, const spActionSet<A>& actionSet) {
  _stateActionPairContainer.addState(
    currentState,
    this->_defaultStateActionValue, actionSet);
  spActionValueMap<A> actionValueMap =
    _buildActionValueMap(actionSet, currentState);
  return this->_getLearningPolicyAction(actionValueMap, actionSet);
}

template<class S, class A>
spActionValueMap<A> ReinforcementLearning<S, A>::_buildActionValueMap(
  const spActionSet<A>& actionSet, const spState<S>& currentState) const {
  spActionValueMap<A> actionValueMap;
  for (const spAction<A>& action : actionSet) {
    actionValueMap[action] = _stateActionPairContainer[
      StateAction<S, A>(currentState, action)];
  }
  return actionValueMap;
}

template<class S, class A>
spAction<A> ReinforcementLearning<S, A>::getAction(
  const spState<S>& currentState, const spActionSet<A>& actionSet) {
  _stateActionPairContainer.addState(currentState,
                                     this->_defaultStateActionValue, actionSet);
  spActionValueMap<A> actionValueMap =
    _buildActionValueMap(actionSet, currentState);
  return this->_controlPolicy->getAction(actionValueMap, actionSet);
}

template<class S, class A>
rl::FLOAT ReinforcementLearning<S, A>::getStateActionValue(
    const StateAction<S, A>& stateAction) {
  return _stateActionPairContainer.getStateActionValue(stateAction);
}

template<class S, class A>
void ReinforcementLearning<S, A>::backUpStateActionPair(
    const StateAction<S, A>& currentStateAction, const rl::FLOAT reward,
    const StateAction<S, A>& nextStateActionPair) {
  // Next state-action value (nSAV) and current state-action value (cSAV).
  rl::FLOAT nSAV = getStateActionValue(nextStateActionPair);
  rl::FLOAT cSAV = getStateActionValue(currentStateAction);
  rl::FLOAT discountRate = this->_discountRate;

  setStateActionValue(
      currentStateAction,
      cSAV + this->_stepSize * (reward + discountRate * nSAV - cSAV));
}

template<class S, class A>
void ReinforcementLearning<S, A>::updateStateAction(
  const StateAction <S, A> &currentStateAction,
  const StateAction <S, A> &nextStateAction,
  const rl::FLOAT reward) {
  (void) reward;
  _stateActionPairContainer.addStateAction(
    currentStateAction, this->_defaultStateActionValue);
  _stateActionPairContainer.addStateAction(
    nextStateAction, this->_defaultStateActionValue);
}

}  // namespace algorithm
}  // namespace rl
