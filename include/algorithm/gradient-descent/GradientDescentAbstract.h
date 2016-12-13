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

#pragma once

#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <memory>
#include <cstdlib>
#include <tuple>

#include "../../declares.h"
#include "../../coding/TileCode.h"

using std::tuple;

using rl::coding::spTileCode;

namespace rl {
namespace algorithm {

/*! \class GradientDescentAbstract
 *  \brief Gradient Descent implementation. Abstract class.
 *  \tparam D Number of dimension.
 *  \tparam NUM_TILINGS Number of tilings.
 *  \tparam STATE_DIM Number of dimension in State.
 *                    This also implies ACTION_DIM = D - STATE_DIM.
 */
template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
class GradientDescentAbstract {
 public:
  static constexpr size_t ACTION_DIM = D - STATE_DIM;

  using StateParam = floatArray<STATE_DIM>;
  using spStateParam = shared_ptr<floatArray<STATE_DIM>>;
  using ActionParam = floatArray<ACTION_DIM>;
  using spActionParam = shared_ptr<floatArray<ACTION_DIM>>;

  /**
   * @param tileCode Type of tile coding.
   * @param stepSize Step size for gradient descent.
   * @param discountRate discount rate for gradient descent.
   * @param lambda How influential is current state-action to ther state-action.
   */
  GradientDescentAbstract(const spTileCode<D, NUM_TILINGS>& tileCode,
                          rl::FLOAT stepSize,
                          rl::FLOAT discountRate,
                          rl::FLOAT lambda);

  /**
   * @return Size of both weight vector and traces vector.
   */
  size_t getSize() const;

  /**
   * Get the value of the parameters in the real space.
   * @param parameters
   * @return corresponding value.
   */
  FLOAT getValueFromParameters(const floatArray<D>& parameters) const;

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
  FEATURE_VECTOR getFeatureVector(const floatArray<D>& parameters) const;

  /**
   * @param currentStateVector array of current states.
   * @param actionVector action taken to get to nextStateVector.
   * @param nextStateVector array of next states.
   * @param reward reward for taking nextAction.
   */
  virtual void updateWeights(
    const GradientDescentAbstract<
      D,
      NUM_TILINGS,
      STATE_DIM>::spStateParam& currentStateVector,
    const GradientDescentAbstract<
      D,
      NUM_TILINGS,
      STATE_DIM>::spActionParam& currentActionVector,
    const GradientDescentAbstract<
      D,
      NUM_TILINGS,
      STATE_DIM>::spStateParam& nextStateVector,
    const FLOAT nextActionValue,
    const FLOAT reward) = 0;

  /**
   * Acquires the action-value map as well as the action with max action.
   * @param actionSet Set of actions.
   * @param nextState Next state.
   * @return {actionValueMap, maxaction}
   */
  tuple<
    spActionValueMap<
      typename GradientDescentAbstract<
        D, NUM_TILINGS, STATE_DIM>::ActionParam>,
    typename GradientDescentAbstract<
      D, NUM_TILINGS, STATE_DIM>::spActionParam>
  buildActionValues(
    const spActionSet<
      GradientDescentAbstract<
        D, NUM_TILINGS, STATE_DIM>::ActionParam>& actionSet,
    const GradientDescentAbstract<
      D, NUM_TILINGS, STATE_DIM>::spStateParam& nextState) const;

  /**
   * @param actionValueMap state-action to value mapping.
   * @return value.
   */
  FLOAT getMaxValue(
    const spActionValueMap<
      GradientDescentAbstract<
        D,
        NUM_TILINGS,
        STATE_DIM>::ActionParam>& actionValueMap) const;

 protected:
  spTileCode<D, NUM_TILINGS> _tileCode;  //!< Tile Code.
  std::vector<rl::FLOAT> _w;  //!< Vector of weights.
  rl::FLOAT _stepSize;  //!< Step Size of the weight update.

  /*! \var _discount
   *
   * Rate, mix with _lambda on how past states influence current.
   */
  rl::FLOAT _discountRate;

  /*! \var _lambda
   *
   * mix with _lambda on how past states influence current.
   */
  rl::FLOAT _lambda;

  // Optimization.
  rl::FLOAT _discountRateTimesLambda;
  rl::FLOAT* _discountRateTimesLambdaArray;
};

template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
using spGradientDescentAbstract =
std::shared_ptr<GradientDescentAbstract<D, NUM_TILINGS, STATE_DIM>>;

template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
GradientDescentAbstract<D, NUM_TILINGS, STATE_DIM>::GradientDescentAbstract(
  const spTileCode<D, NUM_TILINGS>& tileCode,
  rl::FLOAT stepSize,
  rl::FLOAT discountRate,
  rl::FLOAT lambda) :
  _tileCode(tileCode),
  _stepSize(stepSize),
  _discountRate(discountRate),
  _lambda(lambda) {
  _discountRateTimesLambda = _discountRate*_lambda;

  _w = floatVector(this->getSize(), 0);
}

template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
size_t GradientDescentAbstract<D, NUM_TILINGS, STATE_DIM>::getSize() const {
  return _tileCode->getSize();
}

template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
FLOAT
GradientDescentAbstract<D, NUM_TILINGS, STATE_DIM>::getValueFromParameters(
  const floatArray<D>& parameters) const {
  FEATURE_VECTOR fv = std::move(_tileCode->getFeatureVector(parameters));

  return getValueFromFeatureVector(fv);
}

template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
FLOAT
GradientDescentAbstract<D, NUM_TILINGS, STATE_DIM>::getValueFromFeatureVector(
  const FEATURE_VECTOR& fv) const {
  rl::FLOAT sum = 0.0F;

  for (auto f : fv) {
    sum += _w[f];
  }

  return sum;
}

template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
FEATURE_VECTOR
GradientDescentAbstract<D, NUM_TILINGS, STATE_DIM>::getFeatureVector(
  const floatArray<D>& parameters) const {
  return _tileCode->getFeatureVector(parameters);
}

template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
tuple<
  spActionValueMap<
    typename GradientDescentAbstract<
      D, NUM_TILINGS, STATE_DIM>::ActionParam>,
  typename GradientDescentAbstract<
    D, NUM_TILINGS, STATE_DIM>::spActionParam>
GradientDescentAbstract<D, NUM_TILINGS, STATE_DIM>::buildActionValues(
  const spActionSet<GradientDescentAbstract<
    D,
    NUM_TILINGS,
    STATE_DIM>::ActionParam>& actionSet,
  const GradientDescentAbstract<
    D, NUM_TILINGS, STATE_DIM>::spStateParam& nextState) const {
  spActionValueMap<GradientDescentAbstract<
    D,
    NUM_TILINGS,
    STATE_DIM>::ActionParam> actionVectorValueMap;
  typename GradientDescentAbstract<
    D, NUM_TILINGS, STATE_DIM>::spActionParam maxAction;

  typename spActionSet<
    GradientDescentAbstract<
      D,
      NUM_TILINGS,
      STATE_DIM>::ActionParam>::const_iterator maxActionIter =
    actionSet.begin();

  // Build paramCopy = <state1, ..., action1, ...> array.
  floatArray<D> paramCopy;
  std::copy(nextState->begin(),
            nextState->end(),
            paramCopy.begin());
  std::copy((*maxActionIter)->begin(),
            (*maxActionIter)->end(),
            paramCopy.begin() + nextState->size());

  FLOAT maxVal = getValueFromParameters(paramCopy);
  actionVectorValueMap[*maxActionIter] = maxVal;

  typename spActionSet<
    GradientDescentAbstract<
      D,
      NUM_TILINGS,
      STATE_DIM>::ActionParam>::const_iterator iter = maxActionIter;

  iter++;
  for (; iter != actionSet.end(); ++iter) {
    floatArray<D> paramCopy;
    std::copy(nextState->begin(),
              nextState->end(),
              paramCopy.begin());
    std::copy((*maxActionIter)->begin(),
              (*maxActionIter)->end(),
              paramCopy.begin() + nextState->size());

    FLOAT value = getValueFromParameters(paramCopy);
    actionVectorValueMap[*iter] = value;
    if (maxVal < value) {
      maxVal = value;
      maxActionIter = iter;
    }
  }
  maxAction = *maxActionIter;

  return std::make_tuple(actionVectorValueMap, maxAction);
}

}  // namespace algorithm
}  // namespace rl
