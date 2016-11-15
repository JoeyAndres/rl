/**
 * ReinforcementLearningGD.cpp
 */

#include "algorithm/gradient-descent/ReinforcementLearningGD.h"

namespace rl {
namespace algorithm {

ReinforcementLearningGD::ReinforcementLearningGD(
    TileCode& tileCode, rl::FLOAT stepSize, rl::FLOAT discountRate,
    rl::FLOAT lambda, policy::Policy<STATE_CONT, ACTION_CONT >& policy)
    : LearningAlgorithm<STATE_CONT, ACTION_CONT >(policy),
      _gradientDescent(tileCode, stepSize, discountRate, lambda) {
}

void ReinforcementLearningGD::_buildActionValues(
    const set<STATE_CONT >& actionSet, const STATE_CONT& nextState,
    map<ACTION_CONT, FLOAT>& actionValueMap,
    ACTION_CONT& action) {
  _gradientDescent.buildActionValues(actionSet, nextState, actionValueMap, action);
}

void ReinforcementLearningGD::update(
    const StateAction<STATE_CONT, ACTION_CONT >& currentStateAction,
    const STATE_CONT& nextStateVector, const FLOAT reward,
    const set<ACTION_CONT >& actionSet) {
  map<ACTION_CONT, FLOAT> actionValueMap;
  ACTION_CONT maxAction;
  _buildActionValues(actionSet, nextStateVector, actionValueMap, maxAction);
  const ACTION_CONT& nextAction = this->_getLearningPolicyAction(
      actionValueMap, actionSet, maxAction);

  _gradientDescent.updateWeights(currentStateAction.getState(),
                                 currentStateAction.getAction(),
                                 nextStateVector, actionValueMap[nextAction],
                                 reward);
}

ACTION_CONT ReinforcementLearningGD::getAction(
    const STATE_CONT& state, const set<ACTION_CONT >& actionSet) {
  map<ACTION_CONT, FLOAT> actionValueMap;
  ACTION_CONT maxAction;
  _buildActionValues(actionSet, state, actionValueMap, maxAction);
  return this->_learningPolicy->getAction(actionValueMap, actionSet, maxAction);
}

FLOAT ReinforcementLearningGD::getStateActionValue(
    const StateAction<STATE_CONT, ACTION_CONT >& stateAction) {
  return _getStateActionValue(stateAction);
}

FLOAT ReinforcementLearningGD::_getStateActionValue(
    const StateAction<STATE_CONT, ACTION_CONT >& stateAction) {
  vector<FLOAT> copy = stateAction.getState();
  copy.insert(copy.end(), stateAction.getAction().begin(),
              stateAction.getAction().end());
  return _gradientDescent.getValueFromParameters(copy);
}

void ReinforcementLearningGD::reset() {
  LearningAlgorithm<STATE_CONT, ACTION_CONT >::reset();
  _gradientDescent.resetEligibilityTraces();
}

} // namespace Algorithm
} // namespace rl
