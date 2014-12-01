/**
 * GradientDescent.cpp
 */

#ifdef __WIN32__
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

#include <iostream>

#include "GradientDescent.h"

using namespace std;

namespace AI {
namespace Algorithm {
namespace SL {

GradientDescent::GradientDescent(TileCode& tileCode, AI::FLOAT stepSize,
                                 AI::FLOAT discountRate, AI::FLOAT lambda)
    : _tileCode(tileCode) {
  _stepSize = stepSize / _tileCode.getNumTilings();
  _discountRate = discountRate;
  _lambda = lambda;
  _discountRateTimesLambda = _discountRate*_lambda;

#ifdef NO_INTRINSIC
  _e = (AI::FLOAT*)malloc(getSize()*sizeof(AI::FLOAT));  
  _w = (AI::FLOAT*)malloc(getSize()*sizeof(AI::FLOAT));  
#else // With intrinsic.
  _e = (AI::FLOAT*)aligned_alloc(16, getSize()*sizeof(AI::FLOAT));
  _w = (AI::FLOAT*)aligned_alloc(16, getSize()*sizeof(AI::FLOAT));
#endif
  std::fill(_e, _e + getSize(), 0);
  std::fill(_w, _w + getSize(), 0);
}

GradientDescent::~GradientDescent(){
  if(_e){ free(_e); _e = NULL; }
  if(_w){ free(_w); _w = NULL; }
}

size_t GradientDescent::getSize() const {
  return _tileCode.getSize();
}

FLOAT GradientDescent::getValueFromParameters(
    const vector<FLOAT>& parameters) const {
  FEATURE_VECTOR fv = std::move(_tileCode.getFeatureVector(parameters));

  return getValueFromFeatureVector(fv);
}

FLOAT GradientDescent::getValueFromFeatureVector(
    const FEATURE_VECTOR& fv) const {
  AI::FLOAT sum = 0.0F;

  for(auto f : fv){
    sum += _w[f];
  }

  return sum;
}

void GradientDescent::incrementEligibilityTraces(const FEATURE_VECTOR& fv) {
  for (AI::INT f : fv) {
    ++_e[f];
  }
}

void GradientDescent::replaceEligibilityTraces(const FEATURE_VECTOR& fv) {
  for (AI::INT f : fv) {
    _e[f] = 1;
  }
}

void GradientDescent::decreaseEligibilityTraces() {
#ifdef defined(SSE) || defined(SSE2) || defined(SSE3) || defined(SSE4) || \
  defined(SSE4_1) || defined(SSE4_2) || defined(SSE4A)
  __m128d multSSE = _mm_set_pd(_discountRateTimesLambda, _discountRateTimesLambda);
  __m128d* eSSE = (__m128d*)_e;
  size_t n = getSize()>>1;
  for (UINT i = 0; i < n; i++){
    eSSE[i] = _mm_mul_pd(multSSE, eSSE[i]);
  }
#elif AVX
  __m256d multSSE = _mm256_set_pd(_discountRateTimesLambda, _discountRateTimesLambda,
      _discountRateTimesLambda, _discountRateTimesLambda);
  __m256d* eSSE = (__m256d*)_e;
  size_t n = getSize()>>2;
  for (UINT i = 0; i < n; i++){
    eSSE[i] = _mm256_mul_pd(multSSE, eSSE[i]);
  }
#elif defined(NO_INTRINSIC) || defined(MMX)
  size_t n = getSize();
  for (UINT i = 0; i < n; i++){
    _e[i] *= _discountRateTimesLambda;
  }
#endif  // Intrinsic definition test.
}

void GradientDescent::backUpWeights(FLOAT tdError) {
  AI::FLOAT multiplier = _stepSize * tdError;
#ifdef defined(SSE) || defined(SSE2) || defined(SSE3) || defined(SSE4) || \
  defined(SSE4_1) || defined(SSE4_2) || defined(SSE4A)
  __m128d multSSE = _mm_set_pd(multiplier, multiplier);
  __m128d* eSSE = (__m128d*)_e;
  __m128d* wSSE = (__m128d*)_w;
  size_t n = getSize()>>1;
  for (UINT i = 0; i < n; i++){
    wSSE[i] = _mm_add_pd(wSSE[i],_mm_mul_pd(multSSE, eSSE[i]));
  }
#elif AVX
  __m256d multSSE = _mm256_set_pd(multiplier, multiplier, multiplier, multiplier);
  __m256d* eSSE = (__m256d*)_e;
  __m256d* wSSE = (__m256d*)_w;
  size_t n = getSize()>>2;
  for (UINT i = 0; i < n; i++){
    wSSE[i] = _mm256_add_pd(wSSE[i],_mm256_mul_pd(multSSE, eSSE[i]));
  }
#elif defined(NO_INTRINSIC) || defined(MMX)
  size_t n = getSize();
  for (UINT i = 0; i < n-1; i++){
    _w[i] += multiplier*_e[i];
  }  
#endif  // Intrinsic definition test.
}

void GradientDescent::updateWeights(
    const STATE_CONT& currentStateVector,
    const ACTION_CONT& currentActionVector,
    const STATE_CONT& nextStateVector, const FLOAT nextActionValue,
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

FEATURE_VECTOR GradientDescent::getFeatureVector(const vector<FLOAT>& parameters) const {
  return _tileCode.getFeatureVector(parameters);
}

void GradientDescent::buildActionValues(
    const set<ACTION_CONT >& actionSet, const vector<FLOAT>& param,
    map<ACTION_CONT, FLOAT>& actionVectorValueMap, ACTION_CONT& actions) const {
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

void GradientDescent::buildActionValues(
    const set<ACTION_CONT >& actionSet, const vector<FLOAT>& param,
    map<ACTION_CONT, FLOAT>& actionVectorValueMap) const {
  for (const ACTION_CONT& av : actionSet) {
    vector<FLOAT> paramCopy;
    paramCopy.reserve(param.size() + av.size());
    paramCopy.insert(paramCopy.end(), param.begin(), param.end());
    paramCopy.insert(paramCopy.end(), av.begin(), av.end());

    actionVectorValueMap[av] = getValueFromParameters(paramCopy);
  }
}

void GradientDescent::resetEligibilityTraces() {
  std::fill(_e, _e + getSize(), 0);
}

FLOAT GradientDescent::getMaxValue(
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

}  // SL
}  // Algorithm
}  // AI
