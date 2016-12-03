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

namespace rl {
using coding::spTileCode;
namespace algorithm {

/*! \class GradientDescent
 *  \brief Gradient Descent implementation.
 */
class GradientDescent : public GradientDescentAbstract {
 public:
  using GradientDescentAbstract::GradientDescentAbstract;

  void updateWeights(const spStateCont& currentStateVector,
                     const spActionCont& currentActionVector,
                     const spStateCont& nextStateVector,
                     const FLOAT nextActionValue,
                     const FLOAT reward) override;
};

}  // namespace algorithm
}  // namespace rl
