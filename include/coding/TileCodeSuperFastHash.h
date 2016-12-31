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

#include <random>
#include <vector>
#include <array>

#include "../hash/HashSuperFastHash.h"
#include "TileCode.h"

using std::vector;
using std::array;

namespace rl {
namespace coding {

/*! \class TileCodeSuperFastHash
 *  \brief Tile Code using SuperFastHash.
 *  \tparam D Number of dimension.
 *  \tparam NUM_TILINGS Number of tilings.
 *  \tparam WEIGHT_CONT The container object to store the weights.
 */
template <size_t D, size_t NUM_TILINGS, class WEIGHT_CONT = DEFAULT_TILE_CONT>
class TileCodeSuperFastHash : public TileCode<D, NUM_TILINGS, WEIGHT_CONT> {
 public:
  using TileCode<D, NUM_TILINGS, WEIGHT_CONT>::TileCode;

  /**
   * @param dimensionalInfos
   * @param numTilings
   * @param sizeHint If sizeHint is greater than calculated size, then sizeHint
   * will be used instead. The bigger the sizeHint, the less likely is the collision
   * during hashing.
   */
  TileCodeSuperFastHash(const array<DimensionInfo<FLOAT>, D>& dimensionalInfos,
                        size_t sizeHint);

  FEATURE_VECTOR getFeatureVector(
    const floatArray<D>& parameters) const override;
};

template <size_t D, size_t NUM_TILINGS, class WEIGHT_CONT>
TileCodeSuperFastHash<D, NUM_TILINGS, WEIGHT_CONT>::TileCodeSuperFastHash(
  const array<DimensionInfo<FLOAT>, D>& dimensionalInfos,
  size_t sizeHint) :
  TileCode<D, NUM_TILINGS, WEIGHT_CONT>::TileCode(dimensionalInfos, sizeHint) {
}

template <size_t D, size_t NUM_TILINGS, class WEIGHT_CONT>
FEATURE_VECTOR
TileCodeSuperFastHash<D, NUM_TILINGS, WEIGHT_CONT>::getFeatureVector(
  const floatArray<D>& parameters) const {
  vector<rl::INT> tileComponents(this->getDimension() + 1);
  FEATURE_VECTOR fv;

  for (size_t i = 0; i < NUM_TILINGS; i++) {
    for (size_t j = 0; j < this->getDimension(); j++) {
      tileComponents[j] = this->paramToGridValue(parameters.at(j), i, j);
    }

    // Add a unique number_tiling identifier.
    tileComponents[this->getDimension()] = i;

    hash::SuperFastHash hashAlg;
    rl::UINT hashVal = hashAlg.hash(
      (rl::BYTE*) &tileComponents[0],
      tileComponents.size() * sizeof(tileComponents[0]));

    fv.push_back(hashVal % this->_sizeCache);
  }

  return fv;
}

}  // namespace coding
}  // namespace rl
