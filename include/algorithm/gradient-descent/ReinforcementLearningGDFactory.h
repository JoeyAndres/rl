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

#include "../ReinforcementLearningFactory.h"
#include "../LearningAlgorithm.h"
#include "ReinforcementLearningGD.h"

namespace rl {
namespace algorithm {

/*!\class ReinforcementLearningGDFactory
 * \brief Factory method for ReinforcementLearningGDFactory.
 * \tparam D Number of dimension.
 * \tparam NUM_TILINGS Number of tilings.
 * \tparam STATE_DIM Number of dimension in state.
 *                   Implies that action is D - STATE_DIM.
 * \tparam REINFORCEMENT_LEARNING_GD ReinforcementLearningGDAbstract child class.
 */
template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM,
  template <
  size_t E_D,
  size_t E_NUM_TILINGS,
  size_t E_STATE_DIM> class REINFORCEMENT_LEARNING_GD>
class ReinforcementLearningGDFactory :
  public ReinforcementLearningFactory<
    typename ReinforcementLearningGDAbstract<
      D, NUM_TILINGS, STATE_DIM>::StateParam,
    typename ReinforcementLearningGDAbstract<
      D, NUM_TILINGS, STATE_DIM>::ActionParam> {
 public:
  ReinforcementLearningGDFactory(const spTileCode<D, NUM_TILINGS>& tileCode,
                                 rl::FLOAT stepSize,
                                 rl::FLOAT discountRate,
                                 rl::FLOAT lambda,
                                 const typename ReinforcementLearningGDAbstract<
                                   D,
                                   NUM_TILINGS,
                                   STATE_DIM>::spPolicy& policy) {
    this->_instance = spLearningAlgorithm<
      typename ReinforcementLearningGDAbstract<
        D, NUM_TILINGS, STATE_DIM>::StateParam,
      typename ReinforcementLearningGDAbstract<
        D, NUM_TILINGS, STATE_DIM>::ActionParam>(
      new REINFORCEMENT_LEARNING_GD<D, NUM_TILINGS, STATE_DIM>(
        tileCode, stepSize, discountRate, lambda, policy));
  }
};

}  // namespace algorithm
}  // namespace rl
