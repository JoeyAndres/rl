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
#include "../../agent/StateAction.h"
#include "../../coding/TileCode.h"
#include "../LearningAlgorithm.h"
#include "ReinforcementLearningGDAbstract.h"
#include "GradientDescentTileCodeET.h"

using rl::coding::spTileCode;

namespace rl {
namespace algorithm {

/*! \class ReinforcementLearningGDET
 *  \brief Gradient descent implementation of Reinforcement Learning
 *         with Eligibility Traces.
 *  \tparam D Number of dimension.
 *  \tparam NUM_TILINGS Number of tilings.
 *  \tparam STATE_DIM Number of dimension in State. This defaults to D-1.
 *                    This also implies ACTION_DIM = D - STATE_DIM.
 */
template <
  size_t D,
  size_t NUM_TILINGS,
  class WEIGHT_CONT = coding::DEFAULT_TILE_CONT,
  size_t STATE_DIM = D-1>
class ReinforcementLearningGDET :
  public ReinforcementLearningGDAbstract<D, STATE_DIM> {
 public:
  ReinforcementLearningGDET(
    const spTileCode<D, NUM_TILINGS, WEIGHT_CONT>& tileCode,
    rl::FLOAT stepSize,
    rl::FLOAT discountRate,
    rl::FLOAT lambda,
    const typename ReinforcementLearningGDAbstract<
      D, STATE_DIM>::spPolicy& policy);
  virtual ~ReinforcementLearningGDET();
};

template <size_t D, size_t NUM_TILINGS, class WEIGHT_CONT, size_t STATE_DIM>
ReinforcementLearningGDET<
  D, NUM_TILINGS, WEIGHT_CONT, STATE_DIM>::ReinforcementLearningGDET(
  const spTileCode<D, NUM_TILINGS, WEIGHT_CONT>& tileCode,
  rl::FLOAT stepSize,
  rl::FLOAT discountRate,
  rl::FLOAT lambda,
  const typename ReinforcementLearningGDAbstract<
    D, STATE_DIM>::spPolicy& policy) :
  ReinforcementLearningGDAbstract<
    D, STATE_DIM>::ReinforcementLearningGDAbstract(
    tileCode, stepSize, discountRate, lambda, policy) {
  this->_gradientDescent = spGradientDescentAbstract<D, STATE_DIM>(
    new GradientDescentTileCodeET<D, NUM_TILINGS, WEIGHT_CONT, STATE_DIM>(
      tileCode, stepSize, discountRate, lambda));
}

template <size_t D, size_t NUM_TILINGS, class WEIGHT_CONT, size_t STATE_DIM>
ReinforcementLearningGDET<
  D, NUM_TILINGS, WEIGHT_CONT, STATE_DIM>::~ReinforcementLearningGDET() {
}

}  // namespace algorithm
}  // namespace rl
