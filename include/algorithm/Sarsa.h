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
#include <memory>

#include "../agent/StateAction.h"
#include "../policy/Policy.h"
#include "ReinforcementLearning.h"

using std::set;
using std::map;
using std::shared_ptr;

namespace rl {
namespace algorithm {

/*! \class Sarsa
 *  \brief Basic on-policy reinforcement learning algorithm.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 *
 *  The same policy is used for both learning and taking action given state.
 */
template<class S, class A>
class Sarsa : public ReinforcementLearning<S, A> {
 public:
  using SA = StateAction<S, A>;

  /**
   * @param stepSize range \f$[0.0, 1.0]\f$. High step size means faster learning, but
   * less precise convergence.
   * @param discountRate range \f$[0.0, 1.0]\f$. High discount rate means more
   * consideration of future events.
   * @param policy online policy, that is policy used for action selection.
   */
  Sarsa(rl::FLOAT stepSize,
        rl::FLOAT discountRate,
        const policy::spPolicy<S, A>& policy);

 public:
  void update(const SA& currentStateAction,
              const spState<S>& nextState,
              const rl::FLOAT reward,
              const spActionSet<A>& actionSet) override;
};

template <class S, class A>
using spSarsa = shared_ptr<Sarsa<S, A>>;

template<class S, class A>
Sarsa<S, A>::Sarsa(rl::FLOAT stepSize,
                   rl::FLOAT discountRate,
                   const policy::spPolicy<S, A>& policy)
    : ReinforcementLearning<S, A>(stepSize, discountRate, policy) {
  this->setLearningPolicy(policy);
}

// TODO(jandres): Make setLearningPolicy and setPolicy the same.
template<class S, class A>
void Sarsa<S, A>::update(const StateAction<S, A>& currentStateAction,
                         const spState<S>& nextState,
                         const rl::FLOAT reward,
                         const spActionSet<A>& actionSet) {
  spAction<A> nextAction = this->getAction(nextState, actionSet);
  ReinforcementLearning<S, A>::updateStateAction(
    currentStateAction,
    SA(nextState, nextAction),
    reward);
  this->backUpStateActionPair(
    currentStateAction,
    reward,
    SA(nextState, nextAction));
}

}  // namespace algorithm
}  // namespace rl
