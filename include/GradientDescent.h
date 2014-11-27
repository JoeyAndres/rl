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
#include <ammintrin.h> // Define SSE4 intrinsic functions

#include "TileCode.h"

using namespace std;

namespace AI {
namespace Algorithm {
namespace SL {

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
  FEATURE_VECTOR getFeatureVector(const vector<FLOAT>& parameters) const;

  /**
   * Increase the eligibility traces of a given feature vector.
   * Note: This is loads faster than replace elibility traces.
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
  void decreaseEligibilityTraces();

  /**
   * Make all eligibility trace to 0.0F.
   */
  void resetEligibilityTraces();

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
      map<ACTION_CONT, FLOAT>& actionVectorValueMap) const;
  void buildActionValues(
      const set<actionVector<FLOAT> >& actionSet, const vector<FLOAT>& param,
      map<ACTION_CONT, FLOAT>& actionVectorValueMap,
      ACTION_CONT& maxAction) const;

  /**
   * @param actionValueMap state-action to value mapping.
   * @return value.
   */
  FLOAT getMaxValue(
      const map<ACTION_CONT, FLOAT>& actionValueMap) const;

  /**
   * Update weights with tderror.
   * @param tdError
   */
  virtual void backUpWeights(FLOAT tdError);

 protected:
  TileCode& _tileCode;  //!< Tile Code.
  vector<AI::FLOAT> _w;  //!< Vector of weights.
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

  _e = vector<AI::FLOAT>(getSize(), 0);
  _w = vector<FLOAT>(getSize(), 0);
}

inline size_t GradientDescent::getSize() const {
  return _tileCode.getSize();
}

inline FLOAT GradientDescent::getValueFromParameters(
    const vector<FLOAT>& parameters) const {
  FEATURE_VECTOR fv = std::move(_tileCode.getFeatureVector(parameters));

  return getValueFromFeatureVector(fv);
}

inline FLOAT GradientDescent::getValueFromFeatureVector(
    const FEATURE_VECTOR& fv) const {
  AI::FLOAT sum = 0.0F;

  for(auto f : fv){
    sum += _w[f];
  }

  // Optimize Out.
  //sum /= fv.size();

  return sum;
}

inline void GradientDescent::incrementEligibilityTraces(const FEATURE_VECTOR& fv) {
  for (AI::INT f : fv) {
    _e[f]++;
  }
}

inline void GradientDescent::replaceEligibilityTraces(const FEATURE_VECTOR& fv) {
  for (AI::INT f : fv) {
    _e[f] = 1;
  }
}

inline void GradientDescent::decreaseEligibilityTraces() {
  AI::FLOAT multiplier = _discountRate * _lambda;
  __m128d multSSE = _mm_set_pd(multiplier, multiplier);
  __m128d* eSSE = (__m128d*)_e.data();
  size_t n = _e.size()>>1;
  for (UINT i = 0; i < n; i++){    
    eSSE[i] = _mm_mul_pd(multSSE, eSSE[i]);
  }

  // Assumed that the tilecode ensure that _w.size() or _e.size() is even.
}

inline void GradientDescent::backUpWeights(FLOAT tdError) {
  AI::FLOAT multiplier = _stepSize * tdError;
  __m128d multSSE = _mm_set_pd(multiplier, multiplier);
  __m128d* eSSE = (__m128d*)_e.data();
  __m128d* wSSE = (__m128d*)_w.data();
  size_t n = _w.size()>>1;
  for (UINT i = 0; i < n; i++){
    wSSE[i] = _mm_add_pd(wSSE[i],_mm_mul_pd(multSSE, eSSE[i]));
  }

  // Assumed that the tilecode ensure that _w.size() or _e.size() is even.
}

inline void GradientDescent::updateWeights(
    const vector<FLOAT>& currentStateVector,
    const actionVector<FLOAT>& currentActionVector,
    const vector<FLOAT>& nextStateVector, const FLOAT nextActionValue,
    const FLOAT reward) {
  vector<FLOAT> currentStateVectorCopy;
  currentStateVectorCopy.reserve(currentStateVector.size() +
                                 currentActionVector.size());
  currentStateVectorCopy.insert(currentStateVectorCopy.end(),
                                currentStateVector.begin(),
                                currentStateVector.end());
  currentStateVectorCopy.insert(currentStateVectorCopy.end(),
                                currentActionVector.begin(),
                                currentActionVector.end());

  FEATURE_VECTOR currentStateFv = std::move(getFeatureVector(currentStateVectorCopy));
  incrementEligibilityTraces(currentStateFv);

  FLOAT tdError = reward + _discountRate * nextActionValue
      - getValueFromFeatureVector(currentStateFv);

  backUpWeights(tdError);
  // Decrease traces.
  decreaseEligibilityTraces();
}

inline FEATURE_VECTOR GradientDescent::getFeatureVector(const vector<FLOAT>& parameters) const {
  return _tileCode.getFeatureVector(parameters);
}

inline void GradientDescent::buildActionValues(
    const set<actionVector<FLOAT> >& actionSet, const vector<FLOAT>& param,
    map<ACTION_CONT, FLOAT>& actionVectorValueMap,
    ACTION_CONT& actions) const {
  set<ACTION_CONT>::const_iterator maxIter = actionSet.begin();
  vector<FLOAT> pc;
  pc.reserve(param.size() + (*maxIter).size());
  pc.insert(pc.end(), param.begin(), param.end());
  pc.insert(pc.end(), (*maxIter).begin(), (*maxIter).end());
  FLOAT maxVal = getValueFromParameters(pc);
  actionVectorValueMap[*maxIter] = maxVal;

  set<ACTION_CONT>::const_iterator iter = maxIter;
  iter++;
  for (;  iter != actionSet.end(); ++iter) {
    vector<FLOAT> paramCopy;
    paramCopy.reserve(param.size() + (*iter).size());
    paramCopy.insert(paramCopy.end(), param.begin(), param.end());
    paramCopy.insert(paramCopy.end(), (*iter).begin(), (*iter).end());
    
    FLOAT value = getValueFromParameters(paramCopy);
    actionVectorValueMap[*iter] = value;
    if(maxVal < value){
      maxVal = value;
      maxIter = iter;
    }
  }
  actions = *maxIter;
}

inline void GradientDescent::buildActionValues(
    const set<actionVector<FLOAT> >& actionSet, const vector<FLOAT>& param,
    map<ACTION_CONT, FLOAT>& actionVectorValueMap) const {
  for (const actionVector<FLOAT>& av : actionSet) {
    vector<FLOAT> paramCopy;
    paramCopy.reserve(param.size() + av.size());
    paramCopy.insert(paramCopy.end(), param.begin(), param.end());
    paramCopy.insert(paramCopy.end(), av.begin(), av.end());

    actionVectorValueMap[av] = getValueFromParameters(paramCopy);
  }
}

inline void GradientDescent::resetEligibilityTraces() {
  std::fill(_e.begin(), _e.end(), 0);
}

inline FLOAT GradientDescent::getMaxValue(
    const map<ACTION_CONT, FLOAT>& actionValueMap) const {
  // Get max action.
  FLOAT maxValue = actionValueMap.begin()->second;
  for (auto iter = actionValueMap.begin(); iter != actionValueMap.end();
       ++iter) {
    if (iter->second > maxValue) {
      maxValue = iter->second;
    }
  }

  return maxValue;
}

} // namespace SL
} /* namespace Algorithm */
} /* namespace AI */

#endif /* GRADIENTDESCENT_H_ */
