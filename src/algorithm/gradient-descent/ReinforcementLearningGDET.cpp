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

#include "algorithm/gradient-descent/GradientDescentET.h"
#include "algorithm/gradient-descent/ReinforcementLearningGDET.h"

namespace rl {
namespace algorithm {

ReinforcementLearningGDET::ReinforcementLearningGDET (
  TileCode& tileCode, rl::FLOAT stepSize, rl::FLOAT discountRate,
  rl::FLOAT lambda, policy::Policy<stateCont, actionCont >& policy)
  : ReinforcementLearningGDAbstract::ReinforcementLearningGDAbstract(tileCode, stepSize, discountRate, lambda, policy) {
  this->_gradientDescent = shared_ptr<GradientDescentAbstract>(
    new GradientDescentET(tileCode, stepSize, discountRate, lambda)
  );
}

ReinforcementLearningGDET::~ReinforcementLearningGDET() {
}

} // namespace Algorithm
} // namespace rl
