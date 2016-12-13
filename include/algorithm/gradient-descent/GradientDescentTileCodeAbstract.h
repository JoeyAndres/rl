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

#include "../../declares.h"
#include "../../coding/TileCode.h"
#include "GradientDescentAbstract.h"

using rl::coding::spTileCode;

namespace rl {
namespace algorithm {

/*!\class GradientDescentTileCodeAbstract
 * \brief Abstract class for Gradient Descent utilizing tile codes.
 *
 * \tparam D Number of dimension.
 * \tparam NUM_TILINGS Number of tilings.
 * \tparam STATE_DIM Number of dimension in State.
 *                    This also implies ACTION_DIM = D - STATE_DIM.
 */
template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
class GradientDescentTileCodeAbstract :
  public GradientDescentAbstract<D, STATE_DIM> {
 public:
  /**
   * @param tileCode Type of course coding.
   * @param stepSize Step size for gradient descent.
   * @param discountRate discount rate for gradient descent.
   * @param lambda How influential is current state-action to ther state-action.
   */
  GradientDescentTileCodeAbstract(const spTileCode<D, NUM_TILINGS>& tileCode,
                                  rl::FLOAT stepSize,
                                  rl::FLOAT discountRate,
                                  rl::FLOAT lambda);

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

 protected:
  /*!\var _tileCode
   * \brief Refers to the same object as _courseCode but this one is downcast'd
   *        to spTileCode allowing access to tile code specific methods.
   */
  spTileCode<D, NUM_TILINGS> _tileCode;
};

template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
GradientDescentTileCodeAbstract<
  D, NUM_TILINGS, STATE_DIM>::GradientDescentTileCodeAbstract(
  const spTileCode <D, NUM_TILINGS> &tileCode,
  rl::FLOAT stepSize,
  rl::FLOAT discountRate,
  rl::FLOAT lambda) :
  GradientDescentAbstract<D, STATE_DIM>::GradientDescentAbstract(
  tileCode,
  stepSize,
  discountRate,
  lambda) {
  // This is equivalent to _tileCode = _courseCode (downcast'd).
  _tileCode = tileCode;
}

template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
FLOAT
GradientDescentTileCodeAbstract<
  D, NUM_TILINGS, STATE_DIM>::getValueFromFeatureVector(
  const FEATURE_VECTOR& fv) const {
  return _tileCode->getValueFromFeatureVector(fv);
}

template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
FEATURE_VECTOR
GradientDescentTileCodeAbstract<
  D, NUM_TILINGS, STATE_DIM>::getFeatureVector(
  const floatArray<D>& parameters) const {
  return _tileCode->getFeatureVector(parameters);
}

}  // namespace algorithm
}  // namespace rl
