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

#include <vector>
#include <map>

#include "../../declares.h"
#include "../../agent/StateAction.h"
#include "../../coding/TileCode.h"
#include "../LearningAlgorithm.h"
#include "ReinforcementLearningGDAbstract.h"

namespace rl {
namespace algorithm {
using coding::TileCode;

/*! \class ReinforcementLearningGDAbstract
 *  \brief Gradient descent implementation of Reinforcement Learning.
 */
class ReinforcementLearningGD : public ReinforcementLearningGDAbstract {
 public:
  ReinforcementLearningGD(
      TileCode& tileCode, rl::FLOAT stepSize, rl::FLOAT discountRate,
      rl::FLOAT lambda, policy::Policy<stateCont, actionCont >& policy);
  virtual ~ReinforcementLearningGD();
};

} // namespace algorithm
} // namespace rl
