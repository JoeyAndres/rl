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
#include "QLearningGD.h"

namespace rl {
namespace algorithm {

/*!\class QLearningGD
 * \brief Factory method for QLearningGD.
 * \tparam S State data type.
 * \tparam A Action data type.
 */
class QLearningGDFactory :
  public ReinforcementLearningFactory<stateCont, actionCont> {
 public:
  QLearningGDFactory(const spTileCode& tileCode,
                 rl::FLOAT stepSize,
                 rl::FLOAT discountRate,
                 rl::FLOAT lambda,
                 const policy::spPolicy<stateCont, actionCont>& policy) {
    this->_instance = spLearningAlgorithm<stateCont, actionCont>(
      new QLearningGD(
        tileCode,
        stepSize,
        discountRate,
        lambda,
        policy));
  }
};

}  // namespace algorithm
}  // namespace rl
