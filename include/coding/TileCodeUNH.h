/*
 * TileCodeUNH.h
 *
 *  Created on: Jun 15, 2014
 *      Author: jandres
 */

#pragma once

#include <random>

#include "TileCode.h"

namespace rl {
namespace coding {

/*! \class TileCodeUNH
 *  \brief Tile Code using University New Hampshire hash, or UNH.
 */
class TileCodeUNH : public TileCode {
 public:
  TileCodeUNH(vector<DimensionInfo<FLOAT> > dimensionalInfos,
              size_t numTilings);

  TileCodeUNH(vector<DimensionInfo<FLOAT> > dimensionalInfos, size_t numTilings,
              size_t sizeHint);

  /**
   * Hashed the parameter in Real space to a Natural space [0, infinity).
   * @param parameters
   * @return Vector of discretize index.
   */
  virtual FEATURE_VECTOR getFeatureVector(const STATE_CONT& parameters);

  size_t mod(size_t n, size_t k) {
    return (n >= 0) ? n % k : k - 1 - ((-n - 1) % k);
  }

 protected:
  // Optimization parameters.
  vector<rl::FLOAT> _normalization;
};

} // namespace Coding
} /* namespace rl */
