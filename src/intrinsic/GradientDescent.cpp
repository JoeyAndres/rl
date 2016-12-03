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

#include <vector>

#include "algorithm/gradient-descent/GradientDescent.h"

using std::vector;

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

}  // namespace algorithm
}  // namespace rl
