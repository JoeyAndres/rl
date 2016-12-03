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

#include "coding/TileCodeCorrect.h"

namespace rl {
namespace coding {

TileCodeCorrect::TileCodeCorrect(
  const vector<DimensionInfo<FLOAT>>& dimensionalInfos,
  size_t numTilings)
    : TileCode(dimensionalInfos, numTilings) {
}

FEATURE_VECTOR TileCodeCorrect::getFeatureVector(
    const floatVector& parameters) {
  assert(this->getDimension() == parameters.size());
  FEATURE_VECTOR fv;
  fv.resize(this->_numTilings);

  for (rl::INT i = 0; i < this->_numTilings; i++) {
    // x1 + x2*x1.gridSize + x3*x1.gridSize*x2.gridSize + ...
    rl::INT hashedIndex = 0;
    rl::INT mult = 1;
    for (size_t j = 0; j < this->getDimension(); j++) {
      hashedIndex += this->paramToGridValue(parameters.at(j), i, j) * mult;
      mult *= this->_dimensionalInfos[j].GetGridCountReal();
    }

    hashedIndex += mult * i;
    assert(hashedIndex <= this->_sizeCache
    /* Size cache exceeded. Illegal feature vector value. */);
    fv[i] = hashedIndex;
  }
  return fv;
}

}  // namespace coding
}  // namespace rl
