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

#include "DynaQBase.h"
#include "ReinforcementLearning.h"

namespace rl {
namespace algorithm {

/*! \class DynaQRLMP
 *  \brief Abstract class that represents the merge Point for DynaQBase and
 *         Reinforcement Learning.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 *
 *  This class is still so DynaQBase aggregate Reinforcement Learning functions.
 *  Note that although <b>DynaQBase::argMax</b> and <b>DynaQBase::backUpStateActionPair</b>
 *  are used, they both aggregate ReinforcementLearning::argMax and
 *  ReinforcementLearning::backUpStateActionPair.
 */
template<class S, class A>
class DynaQRLMP : public ReinforcementLearning<S, A>, public DynaQBase<S, A> {
  using DynaQBase<S, A>::argMax;
  using DynaQBase<S, A>::backUpStateActionPair;

 public:
  /**
   * @param stepSize range \f$[0.0, 1.0]\f$. High step size means faster learning, but
   * less precise convergence.
   * @param discountRate range \f$[0.0, 1.0]\f$. High discount rate means more
   * consideration of future events.
   * @param policy online policy, that is policy used for action selection.
   * @param simulationIterationCount number of simulations per update/backup.
   * @param stateTransitionGreediness greediness in selecting highest value model.
   * @param stateTransitionStepSize how fast does a model update a value of a
   *                                state-action pair.
   */
  DynaQRLMP(rl::FLOAT stepSize,
            rl::FLOAT discountRate,
            const policy::spPolicy<S, A>& policy,
            rl::UINT simulationIterationCount,
            rl::FLOAT stateTransitionGreediness,
            rl::FLOAT stateTransitionStepSize);

 public:
  // Inherited. Note that, although inherited, documentation have to be
  // reintroduced due to functions aggregating each other.

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
   * Returns the action that will most "likely" gives the highest reward from the
   * current state.
   * @param state the state to apply the argMax to.
   * @param actionSet a set of possible actions.
   * @return the action that will "likely" gives the highest reward.
   */
  virtual spAction<A> argMax(
    const spState<S>& state,
    const spActionSet<A>& actionSet) const;
};

template<class S, class A>
DynaQRLMP<S, A>::DynaQRLMP(
  rl::FLOAT stepSize,
  rl::FLOAT discountRate,
  const policy::spPolicy<S, A>& policy,
  rl::UINT simulationIterationCount,
  rl::FLOAT stateTransitionGreediness,
  rl::FLOAT stateTransitionStepSize)
  : ReinforcementLearning<S, A>(stepSize, discountRate, policy),
    DynaQBase<S, A>(simulationIterationCount, stateTransitionGreediness,
                    stateTransitionStepSize) {
}

template<class S, class A>
void DynaQRLMP<S, A>::backUpStateActionPair(
  const StateAction<S, A>& currentStateAction, const rl::FLOAT reward,
  const StateAction<S, A>& nextStateActionPair) {
  ReinforcementLearning<S, A>::backUpStateActionPair(currentStateAction, reward,
                                                     nextStateActionPair);
}

template<class S, class A>
spAction<A> DynaQRLMP<S, A>::argMax(const spState<S>& state,
                                    const spActionSet<A>& actionSet) const {
  return ReinforcementLearning<S, A>::argMax(state, actionSet);
}

}  // namespace algorithm
}  // namespace rl
