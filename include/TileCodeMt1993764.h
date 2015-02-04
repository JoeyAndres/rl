/*
 * TileCodeMt1993764.h
 *
 *  Created on: Jun 18, 2014
 *      Author: jandres
 */

#pragma once

#include <random>

#include "TileCode.h"

namespace AI {
namespace Algorithm {
namespace SL {

/*! \class TileCodeMt1993764
 *  \brief Tile Code using Mt1993764 hash.2
 */
class TileCodeMt1993764 : public TileCode {
 public:
  /**
   * @param dimensionalInfos
   * @param numTilings
   */
  TileCodeMt1993764(vector<DimensionInfo<FLOAT> >& dimensionalInfos, size_t numTilings);

  /**
   * @param dimensionalInfos
   * @param numTilings
   * @param sizeHint If sizeHint is greater than calculated size, then sizeHint
   * will be used instead. The bigger the sizeHint, the less likely is the collision
   * during hashing.
   */
  TileCodeMt1993764(vector<DimensionInfo<FLOAT> >& dimensionalInfos,
                    size_t numTilings, size_t sizeHint);

  /**
   * Hashed the parameter in Real space to a Natural space [0, infinity).
   * @param parameters
   * @return Vector of discretize index.
   */
  virtual FEATURE_VECTOR getFeatureVector(const STATE_CONT& parameters) override;

 protected:
  std::mt19937_64 _prng;
};

} // namespace SL
} // namespace Algorithm
} // namespace AI
