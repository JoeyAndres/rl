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

class GradientDescentAbstract {
 public:
  /**
   * @param tileCode Type of tile coding.
   * @param stepSize Step size for gradient descent.
   * @param discountRate discount rate for gradient descent.
   * @param lambda How influential is current state-action to ther state-action.
   */
  GradientDescentAbstract(const spTileCode& tileCode,
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
  FLOAT getValueFromParameters(const floatVector& parameters) const;

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
  FEATURE_VECTOR getFeatureVector(const floatVector& parameters) const;

  /**
   * @param currentStateVector array of current states.
   * @param actionVector action taken to get to nextStateVector.
   * @param nextStateVector array of next states.
   * @param reward reward for taking nextAction.
   */
  virtual void updateWeights(const spStateCont& currentStateVector,
                             const spActionCont& currentActionVector,
                             const spStateCont& nextStateVector,
                             const FLOAT nextActionValue,
                             const FLOAT reward) = 0;

  /**
   * Acquires the action-value map as well as the action with max action.
   * @param actionSet Set of actions.
   * @param nextState Next state.
   * @return {actionValueMap, maxaction}
   */
  tuple<spActionValueMap<actionCont>, spActionCont>
  buildActionValues(
    const spActionSet<actionCont>& actionSet,
    const spStateCont& nextState) const;

  /**
   * @param actionValueMap state-action to value mapping.
   * @return value.
   */
  FLOAT getMaxValue(
    const spActionValueMap<actionCont>& actionValueMap) const;

 protected:
  spTileCode _tileCode;  //!< Tile Code.
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

using spGradientDescentAbstract = std::shared_ptr<GradientDescentAbstract>;

}  // namespace algorithm
}  // namespace rl
