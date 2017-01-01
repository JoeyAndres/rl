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

#include "ReinforcementLearningGDFactory.h"
#include "QLearningETGD.h"

namespace rl {
namespace algorithm {

/*!\class QLearningETGD
 * \brief Factory method for QLearningETGD.
 * \tparam D Number of dimension.
 * \tparam NUM_TILINGS Number of tilings.
 * \tparam STATE_DIM Number of dimension in state.
 *                   Implies that action is D - STATE_DIM.
 */
template <
  size_t D,
  size_t NUM_TILINGS,
  class WEIGHT_CONT = coding::DEFAULT_TILE_CONT,
  size_t STATE_DIM = D-1>
class QLearningETGDFactory :
  public ReinforcementLearningGDFactory<
    D, NUM_TILINGS, WEIGHT_CONT, STATE_DIM, QLearningETGD> {
 public:
  using ReinforcementLearningGDFactory<
    D,
    NUM_TILINGS,
    WEIGHT_CONT,
    STATE_DIM,
    QLearningETGD>::ReinforcementLearningGDFactory;
};

}  // namespace algorithm
}  // namespace rl
