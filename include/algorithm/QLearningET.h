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

#include <utility>
#include <map>

#include "../agent/StateAction.h"
#include "EligibilityTraces.h"
#include "../policy/Policy.h"
#include "QLearning.h"

using std::pair;

namespace rl {
namespace algorithm {

/*! \class QLearningET
 *  \brief Like QLearning in that it uses different policy for learning and action
 *         selection. Each iteration, it updates all other states via eligibility
 *         traces, making for faster convergence.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 */
template<class S, class A>
class QLearningET final
  : public EligibilityTraces<S, A>, public QLearning<S, A> {
 public:
  QLearningET(rl::FLOAT stepSize,
              rl::FLOAT discountRate,
              const policy::spPolicy<S, A>& policy,
              rl::FLOAT lambda);

 public:
  virtual void update(const StateAction<S, A>& currentStateAction,
                      const spState<S>& nextState,
                      const rl::FLOAT currentStateActionValue,
                      const spActionSet<A>& actionSet);
};

template<class S, class A>
void QLearningET<S, A>::update(const StateAction<S, A>& currentStateAction,
                               const spAction<S>& nextState,
                               const rl::FLOAT reward,
                               const spActionSet<A>& actionSet) {
  spAction<A> nextAction = this->getLearningAction(nextState, actionSet);
  ReinforcementLearning<S, A>::updateStateAction(
    currentStateAction,
    StateAction<S, A>(nextState, nextAction),
    reward);
  EligibilityTraces<S, A>::_eligibilityTraces.insert(
    std::pair<StateAction<S, A>, rl::FLOAT>(currentStateAction, 0.0F));

  this->_updateEligibilityTraces(currentStateAction,
                                 StateAction<S, A>(nextState, nextAction),
                                 reward, &(this->_stateActionPairContainer),
                                 this->_stepSize, this->_discountRate);
}

template<class S, class A>
QLearningET<S, A>::QLearningET(rl::FLOAT stepSize,
                               rl::FLOAT discountRate,
                               const policy::spPolicy<S, A>& policy,
                               rl::FLOAT lambda)
  : EligibilityTraces<S, A>(lambda),
    QLearning<S, A>(stepSize, discountRate, policy) {
}

}  // namespace algorithm
}  // namespace rl
