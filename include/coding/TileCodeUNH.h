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

#include "../hash/HashUNH.h"
#include "TileCode.h"

using std::vector;

namespace rl {
namespace coding {

/*! \class TileCodeUNH
 *  \brief Tile Code using University New Hampshire hash, or UNH.
 *  \tparam D Number of dimension.
 *  \tparam NUM_TILINGS Number of tilings.
 */
template <size_t D, size_t NUM_TILINGS>
class TileCodeUNH : public TileCode<D, NUM_TILINGS> {
 public:
  using TileCode<D, NUM_TILINGS>::TileCode;

  TileCodeUNH(const array<DimensionInfo<FLOAT>, D>& dimensionalInfos,
              size_t sizeHint);

  FEATURE_VECTOR getFeatureVector(const floatArray<D>& parameters) override;

  size_t mod(size_t n, size_t k) {
    return (n >= 0) ? n % k : k - 1 - ((-n - 1) % k);
  }

 protected:
  // Optimization parameters.
  vector<rl::FLOAT> _normalization;
};

template <size_t D, size_t NUM_TILINGS>
TileCodeUNH<D, NUM_TILINGS>::TileCodeUNH(
  const array<DimensionInfo<FLOAT>, D>& dimensionalInfos,
  size_t sizeHint) :
  TileCode<D, NUM_TILINGS>::TileCode(dimensionalInfos) {
  if (sizeHint > this->_sizeCache) {
    this->_sizeCache = sizeHint;
  }

  _normalization = vector<rl::FLOAT>(this->getDimension());

  for (size_t i = 0; i < this->_dimensionalInfos.size(); i++) {
    _normalization[i] = NUM_TILINGS
      / this->_dimensionalInfos[i].GetRangeDifference();
  }
}

template <size_t D, size_t NUM_TILINGS>
FEATURE_VECTOR TileCodeUNH<D, NUM_TILINGS>::getFeatureVector(
  const floatArray<D>& parameters) {
  FEATURE_VECTOR fv;

  vector<rl::UINT> base(this->getDimension(), 0);
  vector<rl::INT> qStates(this->getDimension());
  for (size_t i = 0; i < this->getDimension(); i++) {
    // Note to floor since casting to integer is not consistent
    // with negative number. Casting is always a number toward zero.
    qStates[i] = floor(parameters.at(i) * _normalization[i]);
  }

  for (size_t i = 0; i < NUM_TILINGS; i++) {
    vector<rl::INT> tileComponents(this->getDimension() + 1);

    for (size_t j = 0; j < this->getDimension(); j++) {
      tileComponents[j] = qStates[j]
        - mod(qStates[j] - base[j], NUM_TILINGS);
      base[j] += 1 + (j * 2);
    }
    tileComponents[this->getDimension()] = i;
    hash::UNH hashAlg;
    fv.push_back(
      hashAlg.hash((rl::BYTE*) &tileComponents[0], this->_sizeCache));
  }

  return fv;
}

}  // namespace coding
}  // namespace rl
