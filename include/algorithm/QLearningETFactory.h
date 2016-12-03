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

#include "ReinforcementLearningFactory.h"
#include "LearningAlgorithm.h"
#include "QLearningET.h"

namespace rl {
namespace algorithm {

/*!\class QLearningET
 * \brief Factory method for QLearningET
 * \tparam S State data type.
 * \tparam A Action data type.
 */
template<class S, class A>
class QLearningETFactory : public ReinforcementLearningFactory<S, A> {
 public:
  QLearningETFactory(FLOAT stepSize,
                 FLOAT discountRate,
                 const policy::spPolicy<S, A>& policy,
                 FLOAT lambda) {
    this->_instance = spLearningAlgorithm<S, A>(
      new QLearningET<S, A>(stepSize, discountRate, policy, lambda));
  }
};

}  // namespace algorithm
}  // namespace rl
