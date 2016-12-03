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

#include "coding/TileCodeSuperFastHash.h"
#include "hash/HashSuperFastHash.h"

namespace rl {
namespace coding {

TileCodeSuperFastHash::TileCodeSuperFastHash(
  const vector<DimensionInfo<FLOAT>>& dimensionalInfos,
  size_t numTilings)
  : TileCode(dimensionalInfos, numTilings) {
}

TileCodeSuperFastHash::TileCodeSuperFastHash(
  const vector<DimensionInfo<FLOAT>>& dimensionalInfos,
  size_t numTilings,
  size_t sizeHint)
  : TileCode(dimensionalInfos, numTilings) {
  if (sizeHint > this->_sizeCache) {
    this->_sizeCache = sizeHint;
  }
}

FEATURE_VECTOR TileCodeSuperFastHash::getFeatureVector(
  const floatVector& parameters) {
  vector<rl::INT> tileComponents(this->getDimension() + 1);
  FEATURE_VECTOR fv;

  for (size_t i = 0; i < this->_numTilings; i++) {
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
