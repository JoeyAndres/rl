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

#include <algorithm>
#include <tuple>
#include <memory>

#include "../../declares.h"
#include "../../agent/StateAction.h"
#include "../../utility/utility.h"
#include "../LearningAlgorithm.h"
#include "GradientDescentAbstract.h"

using std::tuple;
using std::shared_ptr;

using rl::utility::concatArray;
using rl::coding::spCourseCode;

namespace rl {
namespace algorithm {

/*! \class ReinforcementLearningGDAbstract
 *  \brief Gradient descent implementation of Reinforcement Learning.
 *  \tparam D Number of dimension.
 *  \tparam STATE_DIM Number of dimension in State.
 *                    This also implies ACTION_DIM = D - STATE_DIM.
 */
template <size_t D, size_t STATE_DIM>
class ReinforcementLearningGDAbstract
  : public LearningAlgorithm<
    floatArray<STATE_DIM>,
    floatArray<GradientDescentAbstract<D, STATE_DIM>::ACTION_DIM>> {
 public:
  static constexpr size_t ACTION_DIM =
    GradientDescentAbstract<D, STATE_DIM>::ACTION_DIM;

  using StateParam = floatArray<STATE_DIM>;
  using spStateParam = shared_ptr<floatArray<STATE_DIM>>;
  using ActionParam = floatArray<ACTION_DIM>;
  using spActionParam = shared_ptr<floatArray<ACTION_DIM>>;
  using spPolicy = policy::spPolicy<StateParam, ActionParam>;

  /**
   * @param tileCode tileCode implementation to be aggregated.
   * @param stepSize step size indicates how fast increment to a new estimates occur.
   *                 Too big will be fast but will likely cause overestimate. Too low
   *                 will be slow but will likely cause more precise estimates.
   * @param discountRate How much current state influence future states.
   * @param lambda How much current state influence future states (multiplied with discount rate).
   * @param policy Control policy.
   */
  ReinforcementLearningGDAbstract(
    const spCourseCode<D>& tileCode,
    rl::FLOAT stepSize,
    rl::FLOAT discountRate,
    rl::FLOAT lambda,
    const typename ReinforcementLearningGDAbstract<
        D, STATE_DIM>::spPolicy& policy);

  /**
   * @param currentStateAction current state-action vector to apply.
   * @param nextStateVector resulting state by taking state-action pair above.
   * @param reward reward for going to nextStateVector from currentState.
   * @param actionSet set of possible actions.
   */
  virtual void update(
    const StateAction<
      typename ReinforcementLearningGDAbstract<
        D,
        STATE_DIM>::StateParam,
      typename ReinforcementLearningGDAbstract<
        D,
        STATE_DIM>::ActionParam
    >& currentStateAction,
    const ReinforcementLearningGDAbstract<
      D,
      STATE_DIM>::spStateParam& nextStateVector,
    const FLOAT reward,
    const spActionSet<
      ReinforcementLearningGDAbstract<D, STATE_DIM>::ActionParam>& actionSet);

  /**
   * @param state State to take action to.
   * @param actionSet Set of possible actions.
   * @return Action determined by Control Policy.
   */
  virtual
  typename ReinforcementLearningGDAbstract<D, STATE_DIM>::spActionParam
  getAction(
    const typename ReinforcementLearningGDAbstract<
      D, STATE_DIM>::spStateParam& state,
    const spActionSet<
      typename ReinforcementLearningGDAbstract<
        D, STATE_DIM>::ActionParam>& actionSet);

  /**
   * @param stateAction State-action pair to determine value of.
   * @return value of state-action pair.
   */
  virtual FLOAT getStateActionValue(
    const StateAction<
      typename ReinforcementLearningGDAbstract<
        D, STATE_DIM>::StateParam,
      typename ReinforcementLearningGDAbstract<
        D, STATE_DIM>::ActionParam>& stateAction);

  /**
   * Reset routine for an algorithm for every episode.
   */
  virtual void reset();

 protected:
  /**
   * @param stateAction State-action pair to determine value of.
   * @return value of state-actio pair.
   */
  FLOAT _getStateActionValue(
    const StateAction<
      typename ReinforcementLearningGDAbstract<D, STATE_DIM>::StateParam,
      typename ReinforcementLearningGDAbstract<
        D, STATE_DIM>::ActionParam >& stateAction);

  /**
   * Acquires the action-value map as well as the action with max action.
   * @param actionSet Set of actions.
   * @param nextState Next state.
   * @return {actionValueMap, maxaction}
   */
  tuple<
    spActionValueMap<
      typename ReinforcementLearningGDAbstract<
        D, STATE_DIM>::ActionParam>,
    typename ReinforcementLearningGDAbstract<
      D, STATE_DIM>::spActionParam>
  _buildActionValues(
    const spActionSet<
      ReinforcementLearningGDAbstract<D, STATE_DIM>::ActionParam>& actionSet,
    const ReinforcementLearningGDAbstract<
      D, STATE_DIM>::spStateParam& nextState) const;

 protected:
  spGradientDescentAbstract<D, STATE_DIM> _gradientDescent = nullptr;
};

template <size_t D, size_t STATE_DIM>
ReinforcementLearningGDAbstract<D, STATE_DIM>::ReinforcementLearningGDAbstract(
  const spCourseCode<D>& tileCode,
  rl::FLOAT stepSize,
  rl::FLOAT discountRate,
  rl::FLOAT lambda,
  const typename ReinforcementLearningGDAbstract<
    D, STATE_DIM>::spPolicy& policy) :
  LearningAlgorithm<
    ReinforcementLearningGDAbstract<D, STATE_DIM>::StateParam,
    ReinforcementLearningGDAbstract<D, STATE_DIM>::ActionParam>(policy) {
}

template <size_t D, size_t STATE_DIM>
std::tuple<
  spActionValueMap<
    typename ReinforcementLearningGDAbstract<D, STATE_DIM>::ActionParam>,
  typename ReinforcementLearningGDAbstract<D, STATE_DIM>::spActionParam>
ReinforcementLearningGDAbstract<D, STATE_DIM>::_buildActionValues(
  const spActionSet<
    ReinforcementLearningGDAbstract<D, STATE_DIM>::ActionParam>& actionSet,
  const ReinforcementLearningGDAbstract<
    D, STATE_DIM>::spStateParam& nextState) const {
  return _gradientDescent->buildActionValues(actionSet, nextState);
}

template <size_t D, size_t STATE_DIM>
void ReinforcementLearningGDAbstract<D, STATE_DIM>::update(
  const StateAction<
    typename ReinforcementLearningGDAbstract<D, STATE_DIM>::StateParam,
    typename ReinforcementLearningGDAbstract<D, STATE_DIM>::ActionParam
  >& currentStateAction,
  const ReinforcementLearningGDAbstract<
    D,
    STATE_DIM>::spStateParam& nextStateVector, const FLOAT reward,
  const spActionSet<
    ReinforcementLearningGDAbstract<D, STATE_DIM>::ActionParam>& actionSet) {
  auto actionValueAndMaxAction =
    this->_buildActionValues(actionSet, nextStateVector);
  spActionValueMap<
    ReinforcementLearningGDAbstract<
      D, STATE_DIM>::ActionParam> actionValueMap =
    std::get<0>(actionValueAndMaxAction);
  ReinforcementLearningGDAbstract<D, STATE_DIM>::spActionParam maxAction =
    std::get<1>(actionValueAndMaxAction);

  const ReinforcementLearningGDAbstract<
    D, STATE_DIM>::spActionParam& nextAction =
    this->_getLearningPolicyAction(actionValueMap, actionSet, maxAction);

  _gradientDescent->updateWeights(currentStateAction.getState(),
                                  currentStateAction.getAction(),
                                  nextStateVector, actionValueMap[nextAction],
                                  reward);
}

template <size_t D, size_t STATE_DIM>
typename ReinforcementLearningGDAbstract<D, STATE_DIM>::spActionParam
ReinforcementLearningGDAbstract<D, STATE_DIM>::getAction(
  const typename ReinforcementLearningGDAbstract<
    D, STATE_DIM>::spStateParam& state,
  const spActionSet<
    typename ReinforcementLearningGDAbstract<
      D, STATE_DIM>::ActionParam>& actionSet) {
  auto actionValueAndMaxAction =
    this->_buildActionValues(actionSet, state);
  spActionValueMap<
    ReinforcementLearningGDAbstract<
      D, STATE_DIM>::ActionParam> actionValueMap =
    std::get<0>(actionValueAndMaxAction);
  ReinforcementLearningGDAbstract<D, STATE_DIM>::spActionParam maxAction =
    std::get<1>(actionValueAndMaxAction);
  return this->_learningPolicy->getAction(actionValueMap, actionSet, maxAction);
}

template <size_t D, size_t STATE_DIM>
FLOAT ReinforcementLearningGDAbstract<D, STATE_DIM>::getStateActionValue(
  const StateAction<
    ReinforcementLearningGDAbstract<D, STATE_DIM>::StateParam,
    ReinforcementLearningGDAbstract<
      D, STATE_DIM>::ActionParam >& stateAction) {
  return _getStateActionValue(stateAction);
}

template <size_t D, size_t STATE_DIM>
FLOAT ReinforcementLearningGDAbstract<D, STATE_DIM>::_getStateActionValue(
  const StateAction<
    ReinforcementLearningGDAbstract<D, STATE_DIM>::StateParam,
    ReinforcementLearningGDAbstract<
      D, STATE_DIM>::ActionParam >& stateAction) {
  auto copy = *(stateAction.getState());
  auto& stateParams = *stateAction.getState();
  auto& actionParams = *stateAction.getAction();
  auto currentParams = concatArray(stateParams, actionParams);
  return _gradientDescent->getValueFromParameters(currentParams);
}

template <size_t D, size_t STATE_DIM>
void ReinforcementLearningGDAbstract<D, STATE_DIM>::reset() {
  LearningAlgorithm<
    ReinforcementLearningGDAbstract<D, STATE_DIM>::StateParam,
    ReinforcementLearningGDAbstract<D, STATE_DIM>::ActionParam>::reset();
}

}  // namespace algorithm
}  // namespace rl
