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
#include "../utility/FactoryAbstract.h"
#include "TileCode.h"

using std::vector;

namespace rl {
namespace coding {

/*!\class TileCodeFactory
 * \brief Factory method for TileCode. Abstract class.
 * \tparam D Number of dimension.
 * \tparam NUM_TILINGS Number of tilings.
 * \tparam TILE_CODE_CLASS TileCode child that don't utilizes hashing.
 */
template<size_t D, size_t NUM_TILINGS,
  template <size_t E_D, size_t E_NUM_TILINGS> class TILE_CODE_CLASS>
class TileCodeFactory : public FactoryAbstract<TileCode<D, NUM_TILINGS>> {
 public:
  explicit TileCodeFactory(
    const array<DimensionInfo<FLOAT>, D>& dimensionalInfos) {
    this->_instance = spTileCode<D, NUM_TILINGS>(
      new TILE_CODE_CLASS<D, NUM_TILINGS>(dimensionalInfos));
  }
};

}  // namespace coding
}  // namespace rl
