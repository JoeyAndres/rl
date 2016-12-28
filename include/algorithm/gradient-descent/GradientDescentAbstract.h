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
#include "../../utility/utility.h"
#include "../../coding/CourseCode.h"

using std::tuple;

using rl::coding::spCourseCode;

namespace rl {
namespace algorithm {

/*! \class GradientDescentAbstract
 *  \brief Gradient Descent implementation. Abstract class.
 *  \tparam D Number of dimension.
 *  \tparam STATE_DIM Number of dimension in State.
 *                    This also implies ACTION_DIM = D - STATE_DIM.
 */
template <size_t D, size_t STATE_DIM>
class GradientDescentAbstract {
 public:
  static constexpr size_t ACTION_DIM = D - STATE_DIM;

  using StateParam = floatArray<STATE_DIM>;
  using spStateParam = shared_ptr<floatArray<STATE_DIM>>;
  using ActionParam = floatArray<ACTION_DIM>;
  using spActionParam = shared_ptr<floatArray<ACTION_DIM>>;

  /**
   * @param courseCode Type of course coding.
   * @param stepSize Step size for gradient descent.
   * @param discountRate discount rate for gradient descent.
   * @param lambda How influential is current state-action to ther state-action.
   */
  GradientDescentAbstract(const spCourseCode<D>& courseCode,
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
   * @param currentStateVector array of current states.
   * @param actionVector action taken to get to nextStateVector.
   * @param nextStateVector array of next states.
   * @param reward reward for taking nextAction.
   */
  virtual void updateWeights(
    const GradientDescentAbstract<
      D,
      STATE_DIM>::spStateParam& currentStateVector,
    const GradientDescentAbstract<
      D,
      STATE_DIM>::spActionParam& currentActionVector,
    const GradientDescentAbstract<
      D,
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
      typename GradientDescentAbstract<D, STATE_DIM>::ActionParam>,
    typename GradientDescentAbstract<D, STATE_DIM>::spActionParam>
  buildActionValues(
    const spActionSet<
      GradientDescentAbstract<D, STATE_DIM>::ActionParam>& actionSet,
    const GradientDescentAbstract<
      D, STATE_DIM>::spStateParam& nextState) const;

  /**
   * @param actionValueMap state-action to value mapping.
   * @return value.
   */
  FLOAT getMaxValue(
    const spActionValueMap<
      GradientDescentAbstract<
        D,
        STATE_DIM>::ActionParam>& actionValueMap) const;

 protected:
  spCourseCode<D> _courseCode;  //!< Tile Code.
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
};

template <size_t D, size_t STATE_DIM>
using spGradientDescentAbstract =
std::shared_ptr<GradientDescentAbstract<D, STATE_DIM>>;

template <size_t D, size_t STATE_DIM>
GradientDescentAbstract<D, STATE_DIM>::GradientDescentAbstract(
  const spCourseCode<D>& courseCode,
  rl::FLOAT stepSize,
  rl::FLOAT discountRate,
  rl::FLOAT lambda) :
  _courseCode(courseCode),
  _stepSize(stepSize),
  _discountRate(discountRate),
  _lambda(lambda) {
  _discountRateTimesLambda = _discountRate*_lambda;
}

template <size_t D, size_t STATE_DIM>
size_t GradientDescentAbstract<D, STATE_DIM>::getSize() const {
  return _courseCode->getSize();
}

template <size_t D, size_t STATE_DIM>
FLOAT
GradientDescentAbstract<D, STATE_DIM>::getValueFromParameters(
  const floatArray<D>& parameters) const {
  return _courseCode->getValueFromParameters(parameters);
}

template <size_t D, size_t STATE_DIM>
tuple<
  spActionValueMap<
    typename GradientDescentAbstract<D, STATE_DIM>::ActionParam>,
  typename GradientDescentAbstract<D, STATE_DIM>::spActionParam>
GradientDescentAbstract<D, STATE_DIM>::buildActionValues(
  const spActionSet<GradientDescentAbstract<
    D,
    STATE_DIM>::ActionParam>& actionSet,
  const GradientDescentAbstract<
    D, STATE_DIM>::spStateParam& nextState) const {
  spActionValueMap<GradientDescentAbstract<
    D,
    STATE_DIM>::ActionParam> actionVectorValueMap;
  typename GradientDescentAbstract<
    D, STATE_DIM>::spActionParam maxAction;

  typename spActionSet<GradientDescentAbstract<
      D, STATE_DIM>::ActionParam>::const_iterator maxActionIter =
    actionSet.begin();

  floatArray<D> paramCopy =
    std::move(utility::concatArray(*nextState, *(*maxActionIter)));

  FLOAT maxVal = getValueFromParameters(paramCopy);
  actionVectorValueMap[*maxActionIter] = maxVal;

  typename spActionSet<GradientDescentAbstract<
    D, STATE_DIM>::ActionParam>::const_iterator iter = maxActionIter;

  iter++;
  for (; iter != actionSet.end(); ++iter) {
    floatArray<D> paramCopy =
      std::move(utility::concatArray(*nextState, *(*iter)));

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
