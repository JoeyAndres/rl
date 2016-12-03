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
#include <vector>
#include <cassert>
#include <cmath>
#include <memory>

#include "../declares.h"
#include "DimensionInfo.h"

using std::vector;
using std::shared_ptr;

namespace rl {
namespace coding {

/*! \class TileCode
 *  \brief Base object encapsulate tile coding.
 *
 *  For an in-dept explaination of Tile Coding, see
 *  <a href="tileCoding.html">Tile Coding</a>
 */
class TileCode {
 public:
  /**
   * @param dimensionalInfos A vector dimensionalInfos.
   * @param numTilings The higher the value, the more accurate is the
   * 			generalization.
   */
  TileCode(const vector<DimensionInfo<FLOAT>>& dimensionalInfos,
           size_t numTilings);

  /**
   * Hashed the parameter in Real space to a Natural space [0, infinity).
   * @param parameters
   * @param Vector of "discretize" index.
   */
  virtual FEATURE_VECTOR getFeatureVector(const floatVector& parameters) = 0;

  /**
   * @return size of the weight vector.
   */
  size_t getSize() const;

  /**
   * @param numTilings
   */
  void setNumTilings(size_t numTilings);

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
  size_t _numTilings;  //!< How many tilings/also known as sample.

  /*! \var _dimensionalInfos
   *
   * Contains information for each dimension.
   */
  vector<DimensionInfo<FLOAT>> _dimensionalInfos;
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

using spTileCode = shared_ptr<TileCode>;

}  // namespace coding
}  // namespace rl
