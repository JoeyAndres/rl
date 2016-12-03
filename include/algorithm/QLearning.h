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

#include <set>
#include <map>

#include "../agent/StateAction.h"
#include "ReinforcementLearning.h"
#include "../policy/Policy.h"

using std::set;
using std::map;

namespace rl {
namespace algorithm {

/*! \class QLearning
 *  \brief Basic off-policy reinforcement learning algorithm.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 *
 *  Different policy is used for learning and action selection.
 *  Note that default offline/learning policy is EpsilonGreedy
 */
template<class S, class A>
class QLearning : public ReinforcementLearning<S, A> {
 public:
  /**
   * @param stepSize range \f$[0.0, 1.0]\f$. High step size means faster learning, but
   * less precise convergence.
   * @param discountRate range \f$[0.0, 1.0]\f$. High discount rate means more
   * consideration of future events.
   * @param policy online policy, that is policy used for action selection.
   */
  QLearning(rl::FLOAT stepSize, rl::FLOAT discountRate,
            const policy::spPolicy<S, A>& policy);

  void update(const StateAction<S, A>& currentStateAction,
              const spState<S>& nextState, const rl::FLOAT reward,
              const spActionSet<A>& actionSet) override;
};

template<class S, class A>
QLearning<S, A>::QLearning(rl::FLOAT stepSize,
                           rl::FLOAT discountRate,
                           const policy::spPolicy<S, A>& policy)
    : ReinforcementLearning<S, A>(stepSize, discountRate, policy) {
}

template<class S, class A>
void QLearning<S, A>::update(const StateAction<S, A>& currentStateAction,
                             const spState<S>& nextState,
                             const rl::FLOAT reward,
                             const spActionSet<A>& actionSet) {
  // Note: this algorithm is in pg. 145 of Sutton Barto 2nd edition.
  // Q(S, A) <- Q(S, A) + α[ R + γ max a Q(S' , a) − Q(S, A)]
  spAction<A> nextAction = this->getLearningAction(nextState, actionSet);

  ReinforcementLearning<S, A>::updateStateAction(currentStateAction,
                                      StateAction<S, A>(nextState, nextAction),
                                      reward);

  this->backUpStateActionPair(currentStateAction, reward,
                              StateAction<S, A>(nextState, nextAction));
}

}  // namespace algorithm
}  // namespace rl
