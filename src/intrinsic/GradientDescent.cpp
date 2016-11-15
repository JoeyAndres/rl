/**
 * GradientDescent.cpp
 */

#include <iostream>

#include "algorithm/gradient-descent/GradientDescent.h"

using namespace std;

namespace rl {
namespace algorithm {

GradientDescent::GradientDescent(TileCode& tileCode, rl::FLOAT stepSize,
                                 rl::FLOAT discountRate, rl::FLOAT lambda)
    : _tileCode(tileCode) {
  _stepSize = stepSize / _tileCode.getNumTilings();
  _discountRate = discountRate;
  _lambda = lambda;
  _discountRateTimesLambda = _discountRate*_lambda;

#if defined(SSE) || defined(SSE2) || defined(SSE3) || defined(SSE4) || defined(SSE4_1) || defined(SSE4_2) || defined(SSE4A)
  _discountRateTimesLambdaArray = (rl::FLOAT*)aligned_alloc(128, 2*sizeof(rl::FLOAT));
  _discountRateTimesLambdaArray[0] = _discountRateTimesLambda;
  _discountRateTimesLambdaArray[1] = _discountRateTimesLambda;
#elif AVX
  _discountRateTimesLambdaArray = (rl::FLOAT*)aligned_alloc(128, 4*sizeof(rl::FLOAT));
  _discountRateTimesLambdaArray[0] = _discountRateTimesLambda;
  _discountRateTimesLambdaArray[1] = _discountRateTimesLambda;
  _discountRateTimesLambdaArray[2] = _discountRateTimesLambda;
  _discountRateTimesLambdaArray[3] = _discountRateTimesLambda;
#elif NO_INTRINSIC
  _discountRateTimesLambdaArray = &_discountRateTimesLambda;
#endif
  
#if defined(NO_INTRINSIC) || defined(MMX)
  _e = (rl::FLOAT*)malloc(getSize()*sizeof(rl::FLOAT));
  _w = (rl::FLOAT*)malloc(getSize()*sizeof(rl::FLOAT));
#else // Without intrinsic.
  _e = (rl::FLOAT*)aligned_alloc(128, getSize()*sizeof(rl::FLOAT));
  _w = (rl::FLOAT*)aligned_alloc(128, getSize()*sizeof(rl::FLOAT));
#endif
  std::fill(_e, _e + getSize(), 0);
  std::fill(_w, _w + getSize(), 0);
}

GradientDescent::~GradientDescent(){
#if !(defined(NO_INTRINSIC) || defined(MMX))
  delete[] _discountRateTimesLambdaArray;
  _discountRateTimesLambda = NULL;
#endif
  
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
  rl::FLOAT sum = 0.0F;

  for(auto f : fv){
    sum += _w[f];
  }

  return sum;
}

void GradientDescent::incrementEligibilityTraces(const FEATURE_VECTOR& fv) {
  for (rl::INT f : fv) {
    ++_e[f];
  }
}

void GradientDescent::replaceEligibilityTraces(const FEATURE_VECTOR& fv) {
  for (rl::INT f : fv) {
    _e[f] = 1;
  }
}

void GradientDescent::decreaseEligibilityTraces() {  
#if defined(SSE) || defined(SSE2) || defined(SSE3) || defined(SSE4) || defined(SSE4_1) || defined(SSE4_2) || defined(SSE4A)
  __m128d* multSSE = (__m128d*)_discountRateTimesLambdaArray;
  __m128d* eSSE = (__m128d*)_e;
  size_t n = getSize()>>1;
  for (size_t i = 0; i < n; i++){
    eSSE[i] = _mm_mul_pd(*multSSE, eSSE[i]);
  }
#elif AVX
  __m256d* multSSE = (__m256d*) _discountRateTimesLambdaArray;
  __m256d* eSSE = (__m256d*)_e;
  size_t n = getSize()>>2;
  for (size_t i = 0; i < n; i++){
    eSSE[i] = _mm256_mul_pd(*multSSE, eSSE[i]);
  }
#elif defined(NO_INTRINSIC) || defined(MMX)
  size_t n = getSize();
  for (size_t i = 0; i < n; i++){
    _e[i] *= _discountRateTimesLambda;
  }
#else
#error Error: Intrinsic Preprocessor, not recognized
#endif  // Intrinsic definition test.
}

void GradientDescent::backUpWeights(FLOAT tdError) {
  rl::FLOAT multiplier = _stepSize * tdError;
#if defined(SSE) || defined(SSE2) || defined(SSE3) || defined(SSE4) || defined(SSE4_1) || defined(SSE4_2) || defined(SSE4A)
  __m128d multSSE = _mm_set_pd(multiplier, multiplier);
  __m128d* eSSE = (__m128d*)_e;
  __m128d* wSSE = (__m128d*)_w;
  size_t n = getSize()/2;
  for (size_t i = 0; i < n; i++){
    wSSE[i] = _mm_add_pd(wSSE[i],_mm_mul_pd(multSSE, eSSE[i]));
  }
#elif AVX
  __m256d multSSE = _mm256_set_pd(multiplier, multiplier, multiplier, multiplier);
  __m256d* eSSE = (__m256d*)_e;
  __m256d* wSSE = (__m256d*)_w;
  size_t n = getSize()/4;
  for (size_t i = 0; i < n; i++){
    wSSE[i] = _mm256_add_pd(wSSE[i],_mm256_mul_pd(multSSE, eSSE[i]));
  }
#elif defined(NO_INTRINSIC) || defined(MMX)
  size_t n = getSize();
  for (size_t i = 0; i < n-1; i++){
    _w[i] += multiplier*_e[i];
  }
#else
  cout << "Error: Intrinsic Preprocessor, not recognized" << endl;
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
    const set<ACTION_CONT >& actionSet, const vector<FLOAT>& nextState,
    map<ACTION_CONT, FLOAT>& actionVectorValueMap, ACTION_CONT& actions) const {
  set<ACTION_CONT>::const_iterator maxActionIter = actionSet.begin();

  // Build pc = <state1, ..., action1, ...> array.
  vector<FLOAT> pc;
  pc.reserve(nextState.size() + (*maxActionIter).size());
  pc.insert(pc.end(), nextState.begin(), nextState.end());
  pc.insert(pc.end(), (*maxActionIter).begin(), (*maxActionIter).end());

  FLOAT maxVal = getValueFromParameters(pc);
  actionVectorValueMap[*maxActionIter] = maxVal;

  set<ACTION_CONT>::const_iterator iter = maxActionIter;
  iter++;
  for (;  iter != actionSet.end(); ++iter) {
    vector<FLOAT> paramCopy;
    paramCopy.reserve(nextState.size() + (*iter).size());
    paramCopy.insert(paramCopy.end(), nextState.begin(), nextState.end());
    paramCopy.insert(paramCopy.end(), (*iter).begin(), (*iter).end());
    
    FLOAT value = getValueFromParameters(paramCopy);
    actionVectorValueMap[*iter] = value;
    if(maxVal < value){
      maxVal = value;
      maxActionIter = iter;
    }
  }
  actions = *maxActionIter;
}

void GradientDescent::resetEligibilityTraces() {
#if defined(SSE) || defined(SSE2) || defined(SSE3) || defined(SSE4) || defined(SSE4_1) || defined(SSE4_2) || defined(SSE4A)
  __m128d* eSSE = (__m128d*)_e;
  size_t n = getSize()/2;
  for (size_t i = 0; i < n; i++){
    eSSE[i] = _mm_set_pd(0.0F, 0.0F);
  }
#elif AVX
  __m256d* eSSE = (__m256d*)_e;
  size_t n = getSize()/4;
  for (size_t i = 0; i < n; i++){
    eSSE[i] = _mm256_set_pd(0.0F, 0.0F, 0.0F, 0.0F);
  }
#elif defined(NO_INTRINSIC) || defined(MMX)
  std::fill(_e, _e + getSize(), 0);
#else
#error Error: Intrinsic Preprocessor, not recognized.
#endif  // Intrinsic definition test.  
}

FLOAT GradientDescent::getMaxValue(
    const map<ACTION_CONT, FLOAT>& actionValueMap) const {
  // Get max action.
  FLOAT maxValue = actionValueMap.begin()->second;
  for (auto iter = actionValueMap.begin(); iter != actionValueMap.end(); ++iter) {
    if (iter->second > maxValue) {
      maxValue = iter->second;
    }
  }

  return maxValue;
}

}  // Algorithm
}  // rl
