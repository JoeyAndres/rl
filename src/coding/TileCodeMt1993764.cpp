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

#include "coding/TileCodeMt1993764.h"

namespace rl {
namespace coding {

TileCodeMt1993764::TileCodeMt1993764(
    const vector<DimensionInfo<FLOAT>>& dimensionalInfos, size_t numTilings)
    : TileCode(dimensionalInfos, numTilings) {
}

TileCodeMt1993764::TileCodeMt1993764(
    const vector<DimensionInfo<FLOAT>>& dimensionalInfos,
    size_t numTilings,
    size_t sizeHint)
    : TileCode(dimensionalInfos, numTilings) {
  if (sizeHint > this->_sizeCache) {
    this->_sizeCache = sizeHint;
  }
}

FEATURE_VECTOR TileCodeMt1993764::getFeatureVector(
    const floatVector& parameters) {
  vector<rl::INT> tileComponents(this->getDimension() + 1);
  FEATURE_VECTOR fv;

  for (size_t i = 0; i < this->_numTilings; i++) {
    for (size_t j = 0; j < this->getDimension(); j++) {
      tileComponents[j] = this->paramToGridValue(parameters.at(j), i, j);
    }

    // Add a unique number_tiling identifier.
    tileComponents[this->getDimension()] = i;

    std::seed_seq seed1(tileComponents.begin(), tileComponents.end());
    _prng.seed(seed1);

    fv.push_back(_prng() % this->_sizeCache);
  }

  return fv;
}

}  // namespace coding
}  // namespace rl
