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
#include "GradientDescent.h"
#include "ReinforcementLearningGDET.h"

using rl::coding::spTileCode;

namespace rl {
namespace algorithm {

/*! \class SarsaETGD
 *  \brief Gradient Descent with Sarsa implementation (the same policy for
 *         learning and action selection).
 */
class SarsaETGD final: public ReinforcementLearningGDET {
 public:
  SarsaETGD(const spTileCode& tileCode,
            rl::FLOAT stepSize,
            rl::FLOAT discountRate,
            rl::FLOAT lambda,
            const policy::spPolicy<stateCont, actionCont>& policy);
};

}  // namespace algorithm
}  // namespace rl

