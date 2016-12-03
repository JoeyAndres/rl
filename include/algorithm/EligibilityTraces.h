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

#include "../declares.h"
#include "../agent/StateAction.h"
#include "../agent/StateActionPairContainer.h"

using std::map;
using rl::agent::StateAction;

namespace rl {
namespace algorithm {

/*! \class EligibilityTraces
 *  \brief Uses eligibility traces to update state-value pairs. This enables for
 *         fast convergence.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 *
 * As opposed to ordinary Temporal Difference or what's called in the
 * literature as TD(0), eligibility traces TD(\f$\lambda\f$) bridges the
 * gap between TD(0) and Monte Carlo methods. A huge \f$\lambda\f$ means
 * basically back up ranging from terminal state to initial state.
 * Small \f$\lambda\f$ converges to TD(0).
 *
 * Note that there is a performance penalty as result of having
 * to iterate all of state space.
 *
 * TODO: Make another parent class for all other eligibility trace algorithm that contains
 * a merge of rl and Eligibility traces. This way, we can sync some shit.
 *
 * TODO: Connect the reset() to resetEligibilityTraces() function that have yet to be made.
 */
template<class S, class A>
class EligibilityTraces {
 public:
  /**
   * @param lambda A huge lambda means basically back up ranging from
   * terminal state to initial state. Small lambda converges to TD(0).
   */
  explicit EligibilityTraces(rl::FLOAT lambda);

  /**
   * @param lambda A huge \f$\lambda\f$ means
   *                 basically back up ranging from terminal state to initial state.
   *                 Small \f$\lambda\f$ converges to TD(0).
   */
  void setLambda(rl::FLOAT lambda);

  /**
   * @return current lambda.
   */
  rl::FLOAT getLambda() const;

 protected:
  /**
   * Iterate through all states and update each with respect to the their
   * eligibility Trace.
   *
   * @param currentStateAction Current state-action pair.
   * @param nextStateAction Next state-action pair.
   * @param reward Reward for taking state-action pair.
   * @param stateActionPairValueMap A state-action pair container.
   * @param stepSize step size for the update.
   * @param discountRate discount rate for the update.
   */
  virtual void _updateEligibilityTraces(
      const StateAction<S, A>& currentStateAction,
      const StateAction<S, A>& nextStateAction, rl::FLOAT reward,
      StateActionPairContainer<S, A> * const stateActionPairValueMap,
      rl::FLOAT stepSize, rl::FLOAT discountRate);

 protected:
  rl::FLOAT _lambda;
  map<StateAction<S, A>, rl::FLOAT> _eligibilityTraces;
};

template<class S, class A>
EligibilityTraces<S, A>::EligibilityTraces(rl::FLOAT lambda)
    : _lambda(lambda) {
}

template<class S, class A>
void EligibilityTraces<S, A>::setLambda(rl::FLOAT lambda) {
  this->_lambda = lambda;
}

template<class S, class A>
rl::FLOAT EligibilityTraces<S, A>::getLambda() const {
  return _lambda;
}
// todo: encapsulate eligibility traces map to prepare for concurrency.
template<class S, class A>
void EligibilityTraces<S, A>::_updateEligibilityTraces(
    const StateAction<S, A>& currentStateAction,
    const StateAction<S, A>& nextStateAction,
    rl::FLOAT reward,
    StateActionPairContainer<S, A> * const stateActionPairValue,
    rl::FLOAT stepSize,
    rl::FLOAT discountRate) {

  rl::FLOAT tdError = reward
      + discountRate
          * (reward + discountRate * (*stateActionPairValue)[nextStateAction]
            - (*stateActionPairValue)[currentStateAction]);
  _eligibilityTraces[currentStateAction] =
      _eligibilityTraces[currentStateAction] + 1;

  for (auto iter = stateActionPairValue->begin();
      iter != stateActionPairValue->end(); iter++) {
    auto state = iter->first.getState();
    auto action = iter->first.getAction();
    rl::FLOAT value = iter->second;

    stateActionPairValue->setStateActionValue(
        StateAction<S, A>(state, action),
        value
            + stepSize * tdError
                * this->_eligibilityTraces[StateAction<S, A>(state, action)]);

    _eligibilityTraces[StateAction<S, A>(state, action)] = discountRate
        * this->_lambda
        * this->_eligibilityTraces[StateAction<S, A>(state, action)];
  }
}

}  // namespace algorithm
}  // namespace rl

