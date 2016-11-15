/* 
 * File:   TileCode.h
 * Author: jandres
 *
 * Created on June 8, 2014, 8:28 AM
 */

#ifndef _TILE_CODE_H_
#define _TILE_CODE_H_

#include "../declares.h"

#include <cstdint>
#include <random>
#include <stdarg.h>
#include <vector>
#include <cassert>
#include <cmath>

#include "DimensionInfo.h"

using namespace std;

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
  TileCode(vector<DimensionInfo<FLOAT> >& dimensionalInfos, size_t numTilings);

  /**
   * Hashed the parameter in Real space to a Natural space [0, infinity).
   * @param parameters
   * @param Vector of "discretize" index.
   */
  virtual FEATURE_VECTOR getFeatureVector(const STATE_CONT& parameters) = 0;

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
  //void setDimension(size_t dimension);
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
  vector<DimensionInfo<FLOAT> >& _dimensionalInfos;  //!< Contains information for each dimension.
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
  vector<vector<rl::FLOAT> > _randomOffsets;
};

}  // namespace Coding
}  // namespace rl

#endif // _TILE_CODE_H_
