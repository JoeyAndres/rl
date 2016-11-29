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

#include "algorithm/gradient-descent/ReinforcementLearningGDAbstract.h"

namespace rl {
namespace algorithm {

ReinforcementLearningGDAbstract::ReinforcementLearningGDAbstract(
    TileCode& tileCode, rl::FLOAT stepSize, rl::FLOAT discountRate,
    rl::FLOAT lambda, policy::Policy<stateCont, actionCont >& policy)
    : LearningAlgorithm<stateCont, actionCont >(policy) {
}

ReinforcementLearningGDAbstract::~ReinforcementLearningGDAbstract() {
}

void ReinforcementLearningGDAbstract::_buildActionValues(
    const spActionSet<actionCont>& actionSet,
    const spStateCont& nextState,
    spActionValueMap<actionCont>& actionValueMap,
    spActionCont& action) {
  _gradientDescent->buildActionValues(actionSet, nextState, actionValueMap, action);
}

void ReinforcementLearningGDAbstract::update(
    const StateAction<stateCont, actionCont >& currentStateAction,
    const spStateCont& nextStateVector, const FLOAT reward,
    const spActionSet<actionCont>& actionSet) {
  spActionValueMap<actionCont> actionValueMap;
  spActionCont maxAction(new actionCont);
  _buildActionValues(actionSet, nextStateVector, actionValueMap, maxAction);
  const spActionCont& nextAction = this->_getLearningPolicyAction(
      actionValueMap, actionSet, maxAction);

  _gradientDescent->updateWeights(currentStateAction.getState(),
                                 currentStateAction.getAction(),
                                 nextStateVector, actionValueMap[nextAction],
                                 reward);
}

spActionCont ReinforcementLearningGDAbstract::getAction(
    const spStateCont& state, const spActionSet<actionCont>& actionSet) {
  spActionValueMap<actionCont> actionValueMap;
  spActionCont maxAction(new actionCont);
  _buildActionValues(actionSet, state, actionValueMap, maxAction);
  return this->_learningPolicy->getAction(actionValueMap, actionSet, maxAction);
}

FLOAT ReinforcementLearningGDAbstract::getStateActionValue(
    const StateAction<stateCont, actionCont >& stateAction) {
  return _getStateActionValue(stateAction);
}

FLOAT ReinforcementLearningGDAbstract::_getStateActionValue(
    const StateAction<stateCont, actionCont >& stateAction) {
  auto copy = *(stateAction.getState());
  copy.insert(copy.end(), stateAction.getAction()->begin(),
              stateAction.getAction()->end());
  return _gradientDescent->getValueFromParameters(copy);
}

void ReinforcementLearningGDAbstract::reset() {
  LearningAlgorithm<stateCont, actionCont >::reset();
}

} // namespace Algorithm
} // namespace rl
