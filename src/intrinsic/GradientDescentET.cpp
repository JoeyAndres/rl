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

#include "algorithm/gradient-descent/GradientDescentET.h"

namespace rl {
namespace algorithm {

GradientDescentET::GradientDescentET(const spTileCode& tileCode,
                                     rl::FLOAT stepSize,
                                     rl::FLOAT discountRate,
                                     rl::FLOAT lambda) :
  GradientDescentAbstract::GradientDescentAbstract(
    tileCode, stepSize, discountRate, lambda) {
  _e = floatVector(this->getSize(), 0);
}

void GradientDescentET::incrementEligibilityTraces(const FEATURE_VECTOR& fv) {
  for (rl::INT f : fv) {
    ++_e[f];
  }
}

void GradientDescentET::replaceEligibilityTraces(const FEATURE_VECTOR& fv) {
  for (rl::INT f : fv) {
    _e[f] = 1;
  }
}

void GradientDescentET::decreaseEligibilityTraces() {
  size_t n = getSize();
  for (size_t i = 0; i < n; i++) {
    _e[i] *= _discountRateTimesLambda;
  }
}

void GradientDescentET::backUpWeights(FLOAT tdError) {
  rl::FLOAT multiplier = _stepSize * tdError;
  size_t n = getSize();
  for (size_t i = 0; i < n-1; i++) {
    _w[i] += multiplier*_e[i];
  }
}

void GradientDescentET::updateWeights(
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
  incrementEligibilityTraces(currentStateFv);

  FLOAT tdError = reward + _discountRate * nextActionValue
    - getValueFromFeatureVector(currentStateFv);

  backUpWeights(tdError);
  // Decrease traces.
  decreaseEligibilityTraces();
}

void GradientDescentET::resetEligibilityTraces() {
  std::fill(&_e[0], &_e[0] + getSize(), 0);
}

}  // namespace algorithm
}  // namespace rl
