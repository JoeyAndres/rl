/**
 * ReinforcementLearningGD.cpp
 */

#include "algorithm/gradient-descent/ReinforcementLearningGD.h"

namespace rl {
namespace algorithm {

ReinforcementLearningGD::ReinforcementLearningGD(
    TileCode& tileCode, rl::FLOAT stepSize, rl::FLOAT discountRate,
    rl::FLOAT lambda, policy::Policy<stateCont, actionCont >& policy)
    : LearningAlgorithm<stateCont, actionCont >(policy),
      _gradientDescent(tileCode, stepSize, discountRate, lambda) {
}

void ReinforcementLearningGD::_buildActionValues(
    const spActionSet<actionCont>& actionSet,
    const spStateCont& nextState,
    spActionValueMap<actionCont>& actionValueMap,
    spActionCont& action) {
  _gradientDescent.buildActionValues(actionSet, nextState, actionValueMap, action);
}

void ReinforcementLearningGD::update(
    const StateAction<stateCont, actionCont >& currentStateAction,
    const spStateCont& nextStateVector, const FLOAT reward,
    const spActionSet<actionCont>& actionSet) {
  spActionValueMap<actionCont> actionValueMap;
  spActionCont maxAction(new actionCont);
  _buildActionValues(actionSet, nextStateVector, actionValueMap, maxAction);
  const spActionCont& nextAction = this->_getLearningPolicyAction(
      actionValueMap, actionSet, maxAction);

  _gradientDescent.updateWeights(currentStateAction.getState(),
                                 currentStateAction.getAction(),
                                 nextStateVector, actionValueMap[nextAction],
                                 reward);
}

spActionCont ReinforcementLearningGD::getAction(
    const spStateCont& state, const spActionSet<actionCont>& actionSet) {
  spActionValueMap<actionCont> actionValueMap;
  spActionCont maxAction(new actionCont);
  _buildActionValues(actionSet, state, actionValueMap, maxAction);
  return this->_learningPolicy->getAction(actionValueMap, actionSet, maxAction);
}

FLOAT ReinforcementLearningGD::getStateActionValue(
    const StateAction<stateCont, actionCont >& stateAction) {
  return _getStateActionValue(stateAction);
}

FLOAT ReinforcementLearningGD::_getStateActionValue(
    const StateAction<stateCont, actionCont >& stateAction) {
  auto copy = *(stateAction.getState());
  copy.insert(copy.end(), stateAction.getAction()->begin(),
              stateAction.getAction()->end());
  return _gradientDescent.getValueFromParameters(copy);
}

void ReinforcementLearningGD::reset() {
  LearningAlgorithm<stateCont, actionCont >::reset();
  _gradientDescent.resetEligibilityTraces();
}

} // namespace Algorithm
} // namespace rl
