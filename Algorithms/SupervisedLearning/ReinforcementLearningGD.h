/*
 * ReinforcementLearningGD.h
 *
 *  Created on: Jun 12, 2014
 *      Author: jandres
 */

#ifndef REINFORCEMENTLEARNINGGD_H_
#define REINFORCEMENTLEARNINGGD_H_

#include "GlobalHeader.h"

#include <vector>
#include <map>

#include "GradientDescent.h"
#include "GradientDescentCC.h"
#include "StateAction.h"
#include "LearningAlgorithm.h"

namespace AI {
namespace Algorithm {
class ReinforcementLearningGD : public LearningAlgorithm<vector<FLOAT>,
    vector<FLOAT> > {
 public:
  ReinforcementLearningGD(TileCode& tileCode, AI::FLOAT stepSize,
                          AI::FLOAT discountRate, AI::FLOAT lambda,
                          Policy::Policy<vector<FLOAT>, vector<FLOAT> >& policy);

  virtual void update(
      const StateAction<vector<FLOAT>, vector<FLOAT> >& currentStateAction,
      const vector<FLOAT>& nextStateVector, const FLOAT reward,
      const set<vector<FLOAT> >& actionSet);

  virtual const vector<FLOAT>& getAction(const vector<FLOAT>& state,
                                         const set<vector<FLOAT> >& actionSet);

  virtual FLOAT getStateActionValue(
      const StateAction<vector<FLOAT>, vector<FLOAT> >& stateAction);

  virtual void reset();

 protected:
  FLOAT _getStateActionValue(
      const StateAction<vector<FLOAT>, vector<FLOAT> >& stateAction);

  void _buildActionValues(const set<vector<FLOAT> >& actionSet,
                          const vector<FLOAT>& nextState,
                          map<actionVector<FLOAT>, FLOAT>& actionValueMap);

 protected:
  GradientDescent _gradientDescent;
};

ReinforcementLearningGD::ReinforcementLearningGD(
    TileCode& tileCode, AI::FLOAT stepSize, AI::FLOAT discountRate,
    AI::FLOAT lambda, Policy::Policy<vector<FLOAT>, vector<FLOAT> >& policy)
    : LearningAlgorithm<vector<FLOAT>, vector<FLOAT> >(policy),
      _gradientDescent(tileCode, stepSize, discountRate, lambda) {
}

void ReinforcementLearningGD::_buildActionValues(
    const set<vector<FLOAT> >& actionSet, const vector<FLOAT>& nextState,
    map<actionVector<FLOAT>, FLOAT>& actionValueMap) {
  _gradientDescent.buildActionValues(actionSet, nextState, actionValueMap);
}

inline void ReinforcementLearningGD::update(
    const StateAction<vector<FLOAT>, vector<FLOAT> >& currentStateAction,
    const vector<FLOAT>& nextStateVector, const FLOAT reward,
    const set<vector<FLOAT> >& actionSet) {
  map<actionVector<FLOAT>, FLOAT> actionValueMap;
  _buildActionValues(actionSet, nextStateVector, actionValueMap);
  const vector<FLOAT>& nextAction = this->_getLearningPolicyAction(
      actionValueMap, actionSet);
  _gradientDescent.updateWeights(currentStateAction.getState(),
                                 currentStateAction.getAction(),
                                 nextStateVector, actionValueMap[nextAction],
                                 reward);
}

const vector<FLOAT>& ReinforcementLearningGD::getAction(
    const vector<FLOAT>& state, const set<vector<FLOAT> >& actionSet) {
  map<actionVector<FLOAT>, FLOAT> actionValueMap;
  _buildActionValues(actionSet, state, actionValueMap);
  const vector<FLOAT>& nextAction = this->_learningPolicy.getAction(
      actionValueMap, actionSet);
  return nextAction;
}

FLOAT ReinforcementLearningGD::getStateActionValue(
    const StateAction<vector<FLOAT>, vector<FLOAT> >& stateAction) {
  return _getStateActionValue(stateAction);
}

FLOAT ReinforcementLearningGD::_getStateActionValue(
    const StateAction<vector<FLOAT>, vector<FLOAT> >& stateAction) {
  vector<FLOAT> copy = stateAction.getState();
  copy.insert(copy.end(), stateAction.getAction().begin(),
              stateAction.getAction().end());
  return _gradientDescent.getValueFromParameters(copy);
}

void ReinforcementLearningGD::reset() {
  LearningAlgorithm<vector<FLOAT>, vector<FLOAT> >::reset();
  _gradientDescent.resetEligibilityTraces();
}

} /* namespace Algorithm */
} /* namespace AI */

#endif /* REINFORCEMENTLEARNINGGD_H_ */
