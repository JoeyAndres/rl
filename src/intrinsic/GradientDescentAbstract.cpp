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

#include <iostream>
#include <memory>

#include "algorithm/gradient-descent/GradientDescent.h"

using namespace std;

namespace rl {
namespace algorithm {

GradientDescentAbstract::GradientDescentAbstract(TileCode& tileCode,
                                                 rl::FLOAT stepSize,
                                                 rl::FLOAT discountRate,
                                                 rl::FLOAT lambda)
  : _tileCode(tileCode) {
  _stepSize = stepSize / _tileCode.getNumTilings();
  _discountRate = discountRate;
  _lambda = lambda;
  _discountRateTimesLambda = _discountRate*_lambda;

  _w = std::vector<rl::FLOAT>(this->getSize(), 0);
}

size_t GradientDescentAbstract::getSize() const {
  return _tileCode.getSize();
}

FLOAT GradientDescentAbstract::getValueFromParameters(
  const floatVector& parameters) const {
  FEATURE_VECTOR fv = std::move(_tileCode.getFeatureVector(parameters));

  return getValueFromFeatureVector(fv);
}

FLOAT GradientDescentAbstract::getValueFromFeatureVector(
  const FEATURE_VECTOR& fv) const {
  rl::FLOAT sum = 0.0F;

  for(auto f : fv){
    sum += _w[f];
  }

  return sum;
}

FEATURE_VECTOR GradientDescentAbstract::getFeatureVector(const floatVector& parameters) const {
  return _tileCode.getFeatureVector(parameters);
}

void GradientDescentAbstract::buildActionValues(
  const spActionSet<actionCont>& actionSet, const spStateCont& nextState,
  spActionValueMap<actionCont>& actionVectorValueMap, spActionCont& actions) const {
  spActionSet<actionCont>::const_iterator maxActionIter = actionSet.begin();

  // Build pc = <state1, ..., action1, ...> array.
  vector<FLOAT> pc;
  pc.reserve(nextState->size() + (*maxActionIter)->size());
  pc.insert(pc.end(), nextState->begin(), nextState->end());
  pc.insert(pc.end(), (*maxActionIter)->begin(), (*maxActionIter)->end());

  FLOAT maxVal = getValueFromParameters(pc);
  actionVectorValueMap[*maxActionIter] = maxVal;

  spActionSet<actionCont>::const_iterator iter = maxActionIter;
  iter++;
  for (; iter != actionSet.end(); ++iter) {
    vector<FLOAT> paramCopy;
    paramCopy.reserve(nextState->size() + (*iter)->size());
    paramCopy.insert(paramCopy.end(), nextState->begin(), nextState->end());
    paramCopy.insert(paramCopy.end(), (*iter)->begin(), (*iter)->end());

    FLOAT value = getValueFromParameters(paramCopy);
    actionVectorValueMap[*iter] = value;
    if (maxVal < value) {
      maxVal = value;
      maxActionIter = iter;
    }
  }
  actions = *maxActionIter;
}

}  // namespace Algorithm
}  // namespace rl
