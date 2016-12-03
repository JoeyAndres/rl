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

#include <random>

#include "coding/TileCodeUNH.h"
#include "hash/HashUNH.h"

namespace rl {
namespace coding {

TileCodeUNH::TileCodeUNH(
  const vector<DimensionInfo<FLOAT>>& dimensionalInfos,
  size_t numTilings)
  : TileCode(dimensionalInfos, numTilings) {
  _normalization = vector<rl::FLOAT>(this->getDimension());

  for (size_t i = 0; i < this->_dimensionalInfos.size(); i++) {
    _normalization[i] = this->_numTilings
      / this->_dimensionalInfos[i].GetRangeDifference();
  }
}

TileCodeUNH::TileCodeUNH(
  const vector<DimensionInfo<FLOAT>>& dimensionalInfos,
  size_t numTilings,
  size_t sizeHint)
  : TileCode(dimensionalInfos, numTilings) {
  if (sizeHint > this->_sizeCache) {
    this->_sizeCache = sizeHint;
  }

  _normalization = vector<rl::FLOAT>(this->getDimension());

  for (size_t i = 0; i < this->_dimensionalInfos.size(); i++) {
    _normalization[i] = this->_numTilings
      / this->_dimensionalInfos[i].GetRangeDifference();
  }
}

FEATURE_VECTOR TileCodeUNH::getFeatureVector(
  const floatVector& parameters) {
  assert(this->getDimension() == parameters.size());
  FEATURE_VECTOR fv;

  vector<rl::UINT> base(this->getDimension(), 0);
  vector<rl::INT> qStates(this->getDimension());
  for (size_t i = 0; i < this->getDimension(); i++) {
    // Note to floor since casting to integer is not consistent
    // with negative number. Casting is always a number toward zero.
    qStates[i] = floor(parameters.at(i) * _normalization[i]);
  }

  for (size_t i = 0; i < this->_numTilings; i++) {
    vector<rl::INT> tileComponents(this->getDimension() + 1);

    for (size_t j = 0; j < this->getDimension(); j++) {
      tileComponents[j] = qStates[j]
        - mod(qStates[j] - base[j], this->_numTilings);
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
