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

#include "../hash/HashMurmur3.h"
#include "TileCode.h"

using std::vector;
using std::array;

namespace rl {
namespace coding {

/*! \class TileCodeMurMur
 *  \brief Tile Code using MurMur3 hash.
 *  \tparam D Number of dimensions.
 *  \tparam NUM_TILINGS Number of tilings.
 */
template <size_t D, size_t NUM_TILINGS>
class TileCodeMurMur : public TileCode<D, NUM_TILINGS> {
 public:
  using TileCode<D, NUM_TILINGS>::TileCode;
  TileCodeMurMur(const array<DimensionInfo<FLOAT>, D>& dimensionalInfos,
                 size_t sizeHint);
  FEATURE_VECTOR getFeatureVector(
    const floatArray<D>& parameters) const override;
};

template <size_t D, size_t NUM_TILINGS>
TileCodeMurMur<D, NUM_TILINGS>::TileCodeMurMur(
  const array<DimensionInfo<FLOAT>, D>& dimensionalInfos,
  size_t sizeHint) :
  TileCode<D, NUM_TILINGS>::TileCode(dimensionalInfos) {
  this->_sizeCache = sizeHint;
}

template <size_t D, size_t NUM_TILINGS>
FEATURE_VECTOR TileCodeMurMur<D, NUM_TILINGS>::getFeatureVector(
  const floatArray<D>& parameters) const {
  FEATURE_VECTOR fv;

  vector<rl::INT> tileComponents(this->getDimension() + 1);
  for (rl::INT i = 0; i < NUM_TILINGS; i++) {
    for (size_t j = 0; j < this->getDimension(); j++) {
      tileComponents[j] = this->paramToGridValue(parameters.at(j), i, j);
    }

    // Add a unique number_tiling identifier.
    tileComponents[this->getDimension()] = i;

    hash::Murmur3 _hashAlg;
    hash::HashMurmur3Out hash = _hashAlg.hash(
      (rl::BYTE*) tileComponents.data(),
      tileComponents.size() * sizeof(rl::INT));

    fv.push_back(hash.hashVal[0] % this->_sizeCache);
  }

  return fv;
}

}  // namespace coding
}  // namespace rl
