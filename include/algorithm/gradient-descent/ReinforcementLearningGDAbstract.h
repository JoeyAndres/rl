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

#include <tuple>

#include "../../declares.h"
#include "../../agent/StateAction.h"
#include "../LearningAlgorithm.h"
#include "GradientDescent.h"

using std::tuple;

using rl::coding::spTileCode;

namespace rl {
namespace algorithm {

/*! \class ReinforcementLearningGDAbstract
 *  \brief Gradient descent implementation of Reinforcement Learning.
 */
class ReinforcementLearningGDAbstract
  : public LearningAlgorithm<stateCont, actionCont> {
 public:
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
    const spTileCode& tileCode,
    rl::FLOAT stepSize,
    rl::FLOAT discountRate,
    rl::FLOAT lambda,
    const policy::spPolicy<stateCont, actionCont>& policy);

  virtual ~ReinforcementLearningGDAbstract() = 0;

  /**
   * @param currentStateAction current state-action vector to apply.
   * @param nextStateVector resulting state by taking state-action pair above.
   * @param reward reward for going to nextStateVector from currentState.
   * @param actionSet set of possible actions.
   */
  virtual void update(
    const StateAction<stateCont, actionCont >& currentStateAction,
    const spStateCont& nextStateVector, const FLOAT reward,
    const spActionSet<actionCont>& actionSet);

  /**
   * @param state State to take action to.
   * @param actionSet Set of possible actions.
   * @return Action determined by Control Policy.
   */
  virtual spActionCont getAction(const spStateCont& state,
                                 const spActionSet<actionCont>& actionSet);

  /**
   * @param stateAction State-action pair to determine value of.
   * @return value of state-actio pair.
   */
  virtual FLOAT getStateActionValue(
    const StateAction<stateCont, actionCont>& stateAction);

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
    const StateAction<stateCont, actionCont >& stateAction);

  /**
   * Acquires the action-value map as well as the action with max action.
   * @param actionSet Set of actions.
   * @param nextState Next state.
   * @return {actionValueMap, maxaction}
   */
  tuple<spActionValueMap<actionCont>, spActionCont>
  _buildActionValues(
    const spActionSet<actionCont>& actionSet,
    const spStateCont& nextState) const;

 protected:
  spGradientDescentAbstract _gradientDescent = nullptr;
};

}  // namespace algorithm
}  // namespace rl
