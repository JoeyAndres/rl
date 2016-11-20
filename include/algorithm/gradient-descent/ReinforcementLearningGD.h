/*
 * ReinforcementLearningGD.h
 *
 *  Created on: Jun 12, 2014
 *      Author: jandres
 */

#pragma once

#include "../../declares.h"

#include <vector>
#include <map>

#include "GradientDescent.h"
#include "../../agent/StateAction.h"
#include "../LearningAlgorithm.h"

namespace rl {
namespace algorithm {

using namespace coding;

/*! \class ReinforcementLearningGD
 *  \brief Gradient descent implementation of Reinforcement Learning.
 */
class ReinforcementLearningGD : public LearningAlgorithm<stateCont, actionCont> {
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
  ReinforcementLearningGD(
      TileCode& tileCode, rl::FLOAT stepSize, rl::FLOAT discountRate,
      rl::FLOAT lambda, policy::Policy<stateCont, actionCont >& policy);

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
   * @param actionSet set of possible actions.
   * @param nextState state, action just got applied.
   * @param actionValueMap mapping of value for every action.
   * @param action of the highest value. This avoid recomputation later.
   */
  void _buildActionValues(const spActionSet<actionCont>& actionSet,
                          const spStateCont& nextState,
                          spActionValueMap<actionCont>& actionValueMap,
                          spActionCont& maxAction);

 protected:
  GradientDescent _gradientDescent;
};

} // namespace algorithm
} // namespace rl
