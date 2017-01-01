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

#include "../declares.h"
#include "TileCodeHashedFactory.h"
#include "TileCodeSuperFastHash.h"

using std::vector;

namespace rl {
namespace coding {

/*!\class TileCodeSuperFastHashFactory
 * \brief Factory method for TileCodeSuperFastHash.
 * \tparam D Number of dimension.
 * \tparam NUM_TILINGS Number of tilings.
 */
template <size_t D, size_t NUM_TILINGS, class WEIGHT_CONT = DEFAULT_TILE_CONT>
class TileCodeSuperFastHashFactory :
  public TileCodeHashedFactory<
    D, NUM_TILINGS, WEIGHT_CONT, TileCodeSuperFastHash> {
 public:
  using TileCodeFactory<
    D, NUM_TILINGS, WEIGHT_CONT, TileCodeSuperFastHash>::TileCodeFactory;
  using TileCodeHashedFactory<
    D, NUM_TILINGS, WEIGHT_CONT, TileCodeSuperFastHash>::TileCodeFactory;
};

}  // namespace coding
}  // namespace rl
