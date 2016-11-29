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

#include "../../declares.h"
#include "../../coding/TileCode.h"

namespace rl {
using coding::TileCode;
namespace algorithm {

class GradientDescentAbstract {
 public:
  /**
   * @param tileCode Type of tile coding.
   * @param stepSize Step size for gradient descent.
   * @param discountRate discount rate for gradient descent.
   * @param lambda How influential is current state-action to ther state-action.
   */
  GradientDescentAbstract(TileCode& tileCode,
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
   * @param actionSet set of actions.
   * @param param array of current state.
   * @param actionVectorValueMap state-action to value mapping to be returned.
   * @param maxAction max action calculated while building action value map.
   */
  void buildActionValues(
    const spActionSet<actionCont>& actionSet,
    const spStateCont& param,
    spActionValueMap<actionCont>& actionVectorValueMap,
    spActionCont& maxAction) const;

  /**
   * @param actionValueMap state-action to value mapping.
   * @return value.
   */
  FLOAT getMaxValue(
    const spActionValueMap<actionCont>& actionValueMap) const;

 protected:
  TileCode& _tileCode;  //!< Tile Code.
  std::vector<rl::FLOAT> _w;  //!< Vector of weights.
  rl::FLOAT _stepSize;  //!< Step Size of the weight update.
  rl::FLOAT _discountRate;  //!< Discount rate, mix with _lambda on how past states
  //!< influence current.
  rl::FLOAT _lambda;  //!< lambda, mix with _lambda on how past states influence current.

  // Optimization.
  rl::FLOAT _discountRateTimesLambda;
  rl::FLOAT* _discountRateTimesLambdaArray;
};

using spGradientDescentAbstract = std::shared_ptr<GradientDescentAbstract>;

} // namespace algorithm
} // namespace rl
