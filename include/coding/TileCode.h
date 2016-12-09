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

#include <stdarg.h>

#include <cstdint>
#include <random>
#include <cassert>
#include <cmath>
#include <memory>
#include <array>
#include <vector>

#include "../declares.h"
#include "DimensionInfo.h"

using std::array;
using std::vector;
using std::shared_ptr;

namespace rl {
namespace coding {

/*! \class TileCode
 *  \brief Base object encapsulate tile coding.
 *
 *  For an in-dept explanation of Tile Coding, see
 *  <a href="tileCoding.html">Tile Coding</a>
 *
 *  \tparam D Number of dimension.
 *  \tparam NUM_TILINGS Number of tilings.
 */
template<size_t D, size_t NUM_TILINGS>
class TileCode {
 public:
  /**
   * @param dimensionalInfos An array of dimensionalInfos.
   */
  explicit TileCode(const array<DimensionInfo<FLOAT>, D>& dimensionalInfos);

  /**
   * Hashed the parameter in Real space to a Natural space [0, infinity).
   * @param parameters
   * @return Vector of "discretize" index.
   */
  virtual FEATURE_VECTOR getFeatureVector(const floatArray<D>& parameters) = 0;

  /**
   * @return size of the weight vector.
   */
  size_t getSize() const;

  /**
   * @return number of tiling.
   */
  size_t getNumTilings() const;

  /**
   * @param dimension
   */

  /**
   * @return number of dimension.
   */
  size_t getDimension() const;

  /**
   * @param param
   * @param tilingIndex
   * @param dimensionIndex
   * @return
   */
  size_t paramToGridValue(rl::FLOAT param, size_t tilingIndex,
                          size_t dimensionIndex);

 protected:
  /**
   * @return Number of possible grid points.
   */
  size_t _calculateSizeCache();

 protected:
  /*! \var _dimensionalInfos
   *
   * Contains information for each dimension.
   */
  array<DimensionInfo<FLOAT>, D> _dimensionalInfos;
  std::random_device _randomDevice;
  std::default_random_engine _pseudoRNG;

  /*! \var _sizeCache
   *
   *  This implementation is in response to massive performance drop due
   *  unnecessary recalculation of size. Note to update this when possible.
   */
  size_t _sizeCache;

  /*! \var _randomOffsets
   *
   * To avoid recalculating randomness, this aid the consistency of sample.
   * One might say, that its not a real sample if the offsets are pre-computed,
   * and he is right. The problem though is that doing it randomly(pseudo or otherwise)
   * would require ALOT more number tiling to achieve consistency. This alleviates us from
   * that problem and still have a reasonable generalization.
   */
  vector<rl::floatVector> _randomOffsets;
};

template<size_t D, size_t NUM_TILINGS>
using spTileCode = shared_ptr<TileCode<D, NUM_TILINGS>>;

template<size_t D, size_t NUM_TILINGS>
TileCode<D, NUM_TILINGS>::TileCode(
  const array<DimensionInfo<FLOAT>, D>& dimensionalInfos) :
  _dimensionalInfos(dimensionalInfos) {
  // Calculate the size.
  _sizeCache = _calculateSizeCache();

  // Calculate random offsets.
  std::uniform_real_distribution<rl::FLOAT> distribution(0, 1.0F);
  for (size_t i = 0; i < NUM_TILINGS; i++) {
    _randomOffsets.push_back(vector<rl::FLOAT>());
    for (size_t j = 0; j < this->getDimension(); j++) {
      _randomOffsets[i].push_back(
        distribution(_pseudoRNG) * _dimensionalInfos[j].GetOffsets()
          * _dimensionalInfos[j].getGeneralizationScale());
    }
  }
}

template<size_t D, size_t NUM_TILINGS>
size_t TileCode<D, NUM_TILINGS>::getNumTilings() const {
  return NUM_TILINGS;
}

template<size_t D, size_t NUM_TILINGS>
size_t TileCode<D, NUM_TILINGS>::getDimension() const {
  return D;
}

template<size_t D, size_t NUM_TILINGS>
size_t TileCode<D, NUM_TILINGS>::getSize() const {
  return _sizeCache;
}

template<size_t D, size_t NUM_TILINGS>
size_t TileCode<D, NUM_TILINGS>::_calculateSizeCache() {
  // Calculate the size.
  rl::UINT size = 1;
  for (const DimensionInfo<FLOAT>& di : _dimensionalInfos) {
    size *= di.GetGridCountReal();
  }

  size *= NUM_TILINGS;
  return size;
}

template<size_t D, size_t NUM_TILINGS>
size_t TileCode<D, NUM_TILINGS>::paramToGridValue(
  rl::FLOAT param, size_t tilingIndex, size_t dimensionIndex) {
  auto randomOffset =
    _randomOffsets[tilingIndex][dimensionIndex];
  auto dimGeneraliztionScale =
    this->_dimensionalInfos[dimensionIndex].getGeneralizationScale();
  auto dimLowerBound =
    this->_dimensionalInfos[dimensionIndex].getLowerBound();
  auto dimGridCountIdeal =
    this->_dimensionalInfos[dimensionIndex].GetGridCountIdeal();
  auto dimRangeMagnitude =
    this->_dimensionalInfos[dimensionIndex].GetRangeDifference();

  return (
    (
      param +
        randomOffset * dimGeneraliztionScale - dimLowerBound
    ) * dimGridCountIdeal) / dimRangeMagnitude;  // NOLINT: I'd like to make this easy to understand.
}

}  // namespace coding
}  // namespace rl
