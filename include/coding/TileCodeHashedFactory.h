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
#include "TileCodeFactory.h"
#include "TileCode.h"

using std::vector;

namespace rl {
namespace coding {

/*!\class TileCodeFactory
 * \brief Factory method for TileCode. Abstract class.
 * \tparam D Number of dimension.
 * \tparam NUM_TILINGS Number of tilings.
 * \tparam TILE_CODE_CLASS The TileCode child that utilizes hashing.
 */
template<size_t D, size_t NUM_TILINGS, class WEIGHT_CONT,
  template <size_t E_D, size_t E_NUM_TILINGS, class E_WEIGHT_CONT>
  class TILE_CODE_CLASS>
class TileCodeHashedFactory :
  public TileCodeFactory<D, NUM_TILINGS, WEIGHT_CONT, TILE_CODE_CLASS> {
 public:
  TileCodeHashedFactory(const array<DimensionInfo<FLOAT>, D>& dimensionalInfos,
                        size_t sizeHint) {
    this->_instance = spTileCode<D, NUM_TILINGS, WEIGHT_CONT>(
        new TILE_CODE_CLASS<D, NUM_TILINGS, WEIGHT_CONT>(
          dimensionalInfos, sizeHint));
  }
};

}  // namespace coding
}  // namespace rl
