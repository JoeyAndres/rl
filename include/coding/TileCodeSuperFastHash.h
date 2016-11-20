/*
 * TileCode
 *
 *  Created on: Jun 18, 2014
 *      Author: jandres
 */

#pragma once

#include "TileCode.h"

namespace rl {
namespace coding {

/*! \class TileCodeSuperFastHash
 *  \brief Tile Code using SuperFastHash.
 */
class TileCodeSuperFastHash : public TileCode {
 public:
  /**
   * @param dimensionalInfos
   * @param numTilings
   */
  TileCodeSuperFastHash(vector<DimensionInfo<FLOAT> >& dimensionalInfos,
                        size_t numTilings);

  /**
   * @param dimensionalInfos
   * @param numTilings
   * @param sizeHint If sizeHint is greater than calculated size, then sizeHint
   * will be used instead. The bigger the sizeHint, the less likely is the collision
   * during hashing.
   */
  TileCodeSuperFastHash(vector<DimensionInfo<FLOAT> >& dimensionalInfos,
                        size_t numTilings, size_t sizeHint);

  /**
   * Hashed the parameter in Real space to a Natural space [0, infinity).
   * @param parameters
   * @return Vector of discretize index.
   */
  virtual FEATURE_VECTOR getFeatureVector(const floatVector& parameters);
};

} // namespace Coding
} /* namespace rl */
