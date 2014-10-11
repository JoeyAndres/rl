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

class GradientDescent {
 public:
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

  void getFeatureVector(const vector<FLOAT>& parameters,
                        FEATURE_VECTOR& fv) const;
  void incrementEligibilityTraces(const FEATURE_VECTOR& fv);
  void replaceEligibilityTraces(const FEATURE_VECTOR& fv);
  void updateWeights(const vector<FLOAT>& stateVector,
                     const actionVector<FLOAT>& av,
                     const vector<FLOAT>& nextState, const FLOAT reward,
                     const set<actionVector<FLOAT> >& actionSet);
  void updateWeights(const vector<FLOAT>& currentStateVector,
                     const actionVector<FLOAT>& currentActionVector,
                     const vector<FLOAT>& nextStateVector,
                     const vector<FLOAT>& nextAction, const FLOAT reward);
  void updateWeights(const vector<FLOAT>& currentStateVector,
                     const actionVector<FLOAT>& currentActionVector,
                     const vector<FLOAT>& nextStateVector,
                     const FLOAT nextActionValue, const FLOAT reward);
  void resetEligibilityTraces();
  void buildActionValues(
      const set<actionVector<FLOAT> >& actionSet, const vector<FLOAT>& param,
      map<actionVector<FLOAT>, FLOAT>& actionVectorValueMap) const;
  FLOAT getMaxValue(
      const map<actionVector<FLOAT>, FLOAT>& actionValueMap) const;

  virtual void decreaseEligibilityTraces();
  virtual void backUpWeights(FLOAT tdError);
 protected:
  TileCode& _tileCode;
  vector<FLOAT> _w;
  vector<AI::FLOAT> _e;
  AI::FLOAT _stepSize;
  AI::FLOAT _discountRate;
  AI::FLOAT _lambda;
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
