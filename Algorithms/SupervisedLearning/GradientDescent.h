/*
 * GradientDescent.h
 *
 *  Created on: Jun 11, 2014
 *      Author: jandres
 */

#ifndef GRADIENTDESCENT_H_
#define GRADIENTDESCENT_H_

#include "GlobalHeader.h"

#include <set>
#include <vector>
#include <iostream>

#include "TileCode.h"

using namespace std;

namespace AI {
namespace Algorithm {

template<typename FLOAT = AI::FLOAT>
using actionVector = vector<FLOAT>;

/*! \class GradientDescent
 *  \brief Early implementation of Gradient Descent specialized for Tile Coding.
 *
 *  This is still an early implementation of Gradient Descent,
 */
class GradientDescent {
 public:
  /**
   * @param tileCode Type of tile coding.
   * @param stepSize Step size for gradient descent.
   * @param discountRate discount rate for gradient descent.
   * @param lambda How influential is current state-action to ther state-action.
   */
  GradientDescent(TileCode& tileCode, AI::FLOAT stepSize,
                  AI::FLOAT discountRate, AI::FLOAT lambda);

  /**
   * @return Size of both weight vector and traces vector.
   */
  size_t getSize() const;

  /**
   * Get the value of the parameters in the real space.
   * @param parameters
   * @return corresponding value.
   */
  FLOAT getValueFromParameters(const vector<FLOAT>& parameters) const;

  /**
   * Get the value of the parameters in the real space.
   * @param featureVector
   * @return corresponding value.
   */
  FLOAT getValueFromFeatureVector(const FEATURE_VECTOR& fv) const;

  /**
   * @param parameters parameters.
   * @param fv feature vector output. Feature vector are samples taken around
   *           the parameters in the n-dimension tilecde.
   */
  void getFeatureVector(const vector<FLOAT>& parameters,
                        FEATURE_VECTOR& fv) const;

  /**
   * Increase the eligibility traces of a given feature vector.
   * @param fv feature vector.
   */
  void incrementEligibilityTraces(const FEATURE_VECTOR& fv);

  /**
   * Replace the eligibility traces for each feature vector by 1.0F.
   * @param fv feature vector.
   */
  void replaceEligibilityTraces(const FEATURE_VECTOR& fv);

  /**
   * Decrease each eligibility traces by eligibility traces and discount rate $(\lambda)$
   */
  virtual void decreaseEligibilityTraces();

  /**
   * Make all eligibility trace to 0.0F.
   */
 void resetEligibilityTraces();

  /**
   * @param stateVector vector of states.
   * @param av action vector.
   * @param nextState next state vector.
   * @param reward reward for going to takeing av in sateVector.
   * @param actionSet Set of action vector.
   */
  void updateWeights(const vector<FLOAT>& stateVector,
                     const actionVector<FLOAT>& av,
                     const vector<FLOAT>& nextState, const FLOAT reward,
                     const set<actionVector<FLOAT> >& actionSet);

  /**
   * @param currentStateVector array of current states.
   * @param currentActionVector array of action taken to get to currentStateVector..
   * @param nextStateVector array of next states.
   * @param nextAction array of next action taken to get to nextStateVector.
   * @param reward reward for taking nextAction.
   */
  void updateWeights(const vector<FLOAT>& currentStateVector,
                     const actionVector<FLOAT>& currentActionVector,
                     const vector<FLOAT>& nextStateVector,
                     const vector<FLOAT>& nextAction, const FLOAT reward);

  /**
   * @param currentStateVector array of current states.
   * @param actionVector action taken to get to nextStateVector.
   * @param nextStateVector array of next states.
   * @param reward reward for taking nextAction.
   */
  void updateWeights(const vector<FLOAT>& currentStateVector,
                     const actionVector<FLOAT>& currentActionVector,
                     const vector<FLOAT>& nextStateVector,
                     const FLOAT nextActionValue, const FLOAT reward);

  /**
   * @param actionSet set of actions.
   * @param param array of current state.
   * @param actionVectorValueMap state-action to value mapping to be returned.
   */
  void buildActionValues(
      const set<actionVector<FLOAT> >& actionSet, const vector<FLOAT>& param,
      map<actionVector<FLOAT>, FLOAT>& actionVectorValueMap) const;

  /**
   * @param actionValueMap state-action to value mapping.
   * @return value.
   */
  FLOAT getMaxValue(
      const map<actionVector<FLOAT>, FLOAT>& actionValueMap) const;

  /**
   * Update weights with tderror.
   * @param tdError
   */
  virtual void backUpWeights(FLOAT tdError);

 protected:
  TileCode& _tileCode;  //!< Tile Code.
  vector<FLOAT> _w;  //!< Vector of weights.
  vector<AI::FLOAT> _e;  //!< Vector of eligibility traces.
  AI::FLOAT _stepSize;  //!< Step Size of the weight update.
  AI::FLOAT _discountRate;  //!< Discount rate, mix with _lambda on how past states
                            //!< influence current.
  AI::FLOAT _lambda;  //!< lambda, mix with _lambda on how past states influence current.
};

GradientDescent::GradientDescent(TileCode& tileCode, AI::FLOAT stepSize,
                                 AI::FLOAT discountRate, AI::FLOAT lambda)
    : _tileCode(tileCode) {
  _stepSize = stepSize / _tileCode.getNumTilings();
  _discountRate = discountRate;
  _lambda = lambda;

  _e = vector < AI::FLOAT > (getSize(), 0);
  _w = vector < FLOAT > (getSize(), 0);
}

size_t AI::Algorithm::GradientDescent::getSize() const {
  return _tileCode.getSize();
}

FLOAT GradientDescent::getValueFromParameters(
    const vector<FLOAT>& parameters) const {
  FEATURE_VECTOR fv;
  _tileCode.getFeatureVector(parameters, fv);

  return getValueFromFeatureVector(fv);
}

FLOAT GradientDescent::getValueFromFeatureVector(
    const FEATURE_VECTOR& fv) const {
  AI::FLOAT sum = 0.0F;
  for (AI::UINT f : fv) {
    sum += _w[f];
  }
  sum /= fv.size();

  return sum;
}

void GradientDescent::incrementEligibilityTraces(const FEATURE_VECTOR& fv) {
  for (AI::INT f : fv) {
    _e[f] += 1.0F;
  }
}

void GradientDescent::replaceEligibilityTraces(const FEATURE_VECTOR& fv) {
  for (AI::INT f : fv) {
    _e[f] = 1.0F;
  }
}

void GradientDescent::decreaseEligibilityTraces() {
  AI::FLOAT multiplier = _discountRate * _lambda;
  for (size_t i = 0; i < getSize(); i++) {
    _e[i] = multiplier * _e[i];
  }
}

void GradientDescent::updateWeights(
    const vector<FLOAT>& stateVector, const actionVector<FLOAT>& av,
    const vector<FLOAT>& nextState, const FLOAT reward,
    const set<actionVector<FLOAT> >& actionSet) {
  map<actionVector<FLOAT>, FLOAT> actionValueMap;
  buildActionValues(actionSet, nextState, actionValueMap);
  FLOAT maxValue = getMaxValue(actionValueMap);

  vector<FLOAT> stateVectorCopy = stateVector;
  for (const FLOAT& action : av) {
    stateVectorCopy.push_back(action);
  }

  FEATURE_VECTOR fv;
  getFeatureVector(stateVectorCopy, fv);
  incrementEligibilityTraces(fv);

  FLOAT tdError = reward + _discountRate * maxValue
      - getValueFromFeatureVector(fv);

  AI::FLOAT multiplier = _stepSize * tdError;
  for (size_t i = 0; i < getSize(); i++) {
    _w[i] += multiplier * _e[i];
  }

  // Decrease traces.
  decreaseEligibilityTraces();
}

inline void GradientDescent::updateWeights(
    const vector<FLOAT>& currentStateVector,
    const actionVector<FLOAT>& currentActionVector,
    const vector<FLOAT>& nextStateVector, const vector<FLOAT>& nextActionVector,
    const FLOAT reward) {

  vector<FLOAT> currentStateVectorCopy = currentStateVector;
  for (const FLOAT& action : currentActionVector) {
    currentStateVectorCopy.push_back(action);
  }

  FEATURE_VECTOR currentStateFv;
  getFeatureVector(currentStateVectorCopy, currentStateFv);
  incrementEligibilityTraces(currentStateFv);

  vector<FLOAT> nextStateVectorCopy = nextStateVector;
  for (const FLOAT& action : nextActionVector) {
    nextStateVectorCopy.push_back(action);
  }

  FEATURE_VECTOR nextStateFv;
  getFeatureVector(nextStateVectorCopy, nextStateFv);

  FLOAT tdError = reward
      + _discountRate * getValueFromFeatureVector(nextStateFv)
      - getValueFromFeatureVector(currentStateFv);

  AI::FLOAT multiplier = _stepSize * tdError;
  for (size_t i = 0; i < getSize(); i++) {
    _w[i] += multiplier * _e[i];
  }

  // Decrease traces.
  decreaseEligibilityTraces();
}

void GradientDescent::backUpWeights(FLOAT tdError) {
  AI::FLOAT multiplier = _stepSize * tdError;
  for (size_t i = 0; i < getSize(); i++) {
    _w[i] += multiplier * _e[i];
  }
}

inline void GradientDescent::updateWeights(
    const vector<FLOAT>& currentStateVector,
    const actionVector<FLOAT>& currentActionVector,
    const vector<FLOAT>& nextStateVector, const FLOAT nextActionValue,
    const FLOAT reward) {
  vector<FLOAT> currentStateVectorCopy = currentStateVector;
  for (const FLOAT& action : currentActionVector) {
    currentStateVectorCopy.push_back(action);
  }

  FEATURE_VECTOR currentStateFv;
  getFeatureVector(currentStateVectorCopy, currentStateFv);
  incrementEligibilityTraces(currentStateFv);

  FLOAT tdError = reward + _discountRate * nextActionValue
      - getValueFromFeatureVector(currentStateFv);

  backUpWeights(tdError);
  // Decrease traces.
  decreaseEligibilityTraces();
}

void GradientDescent::getFeatureVector(const vector<FLOAT>& parameters,
                                       FEATURE_VECTOR& fv) const {
  _tileCode.getFeatureVector(parameters, fv);
}

void GradientDescent::buildActionValues(
    const set<actionVector<FLOAT> >& actionSet, const vector<FLOAT>& param,
    map<actionVector<FLOAT>, FLOAT>& actionVectorValueMap) const {
  vector<FLOAT> paramCopy = param;

  for (const actionVector<FLOAT>& av : actionSet) {
    for (const FLOAT& a : av) {
      paramCopy.push_back(a);
    }

    actionVectorValueMap[av] = getValueFromParameters(paramCopy);

    for (const FLOAT& a : av) {
      (void) a;
      paramCopy.pop_back();
    }
  }
}

inline void GradientDescent::resetEligibilityTraces() {
  std::fill(_e.begin(), _e.end(), 0);
}

FLOAT GradientDescent::getMaxValue(
    const map<actionVector<FLOAT>, FLOAT>& actionValueMap) const {
  // Get max action.
  FLOAT maxValue = actionValueMap.begin()->second;
  for (auto iter = actionValueMap.begin(); iter != actionValueMap.end();
      iter++) {
    if (iter->second > maxValue) {
      maxValue = iter->second;
    }
  }

  return maxValue;
}
} /* namespace Algorithm */
} /* namespace AI */

#endif /* GRADIENTDESCENT_H_ */
