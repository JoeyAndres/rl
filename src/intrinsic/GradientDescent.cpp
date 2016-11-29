/**
 * GradientDescent.cpp
 */

#include <iostream>
#include <memory>

#include "algorithm/gradient-descent/GradientDescent.h"

using namespace std;

namespace rl {
namespace algorithm {

void GradientDescent::updateWeights(
  const spStateCont& currentStateVector,
  const spActionCont& currentActionVector,
  const spStateCont& nextStateVector,
  const FLOAT nextActionValue,
  const FLOAT reward) {
  vector<FLOAT> currentStateVectorCopy;
  currentStateVectorCopy.reserve(currentStateVector->size() +
    currentActionVector->size());
  currentStateVectorCopy.insert(currentStateVectorCopy.end(),
                                currentStateVector->begin(),
                                currentStateVector->end());
  currentStateVectorCopy.insert(currentStateVectorCopy.end(),
                                currentActionVector->begin(),
                                currentActionVector->end());

  FEATURE_VECTOR currentStateFv =
    std::move(getFeatureVector(currentStateVectorCopy));

  FLOAT tdError = reward + _discountRate * nextActionValue
    - getValueFromFeatureVector(currentStateFv);

  for (auto f : currentStateFv) {
    _w[f] += tdError * this->_stepSize;
  }
}

}  // namespace Algorithm
}  // namespace rl
