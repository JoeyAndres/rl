/*
 * TileCode
 *
 *  Created on: Jun 18, 2014
 *      Author: jandres
 */

#ifndef TILECODESUPERFASTHASH_H_
#define TILECODESUPERFASTHASH_H_

#include "TileCode.h"
#include "HashSuperFastHash.h"
#include "xxhash.h"

namespace AI {
namespace Algorithm {
namespace SL {
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
  virtual FEATURE_VECTOR getFeatureVector(const STATE_CONT& parameters);
};

inline TileCodeSuperFastHash::TileCodeSuperFastHash(vector<DimensionInfo<FLOAT> >& dimensionalInfos,
                                                    size_t numTilings)
    : TileCode(dimensionalInfos, numTilings) {
}

inline TileCodeSuperFastHash::TileCodeSuperFastHash(vector<DimensionInfo<FLOAT> >& dimensionalInfos,
                                                    size_t numTilings,
    size_t sizeHint)
    : TileCode(dimensionalInfos, numTilings) {
  if (sizeHint > this->_sizeCache) {
    this->_sizeCache = sizeHint;
  }
}

inline FEATURE_VECTOR TileCodeSuperFastHash::getFeatureVector(
    const STATE_CONT& parameters) {
  vector<AI::INT> tileComponents(this->getDimension() + 1);
  FEATURE_VECTOR fv;
  
  for (size_t i = 0; i < this->_numTilings; i++) {
    for (size_t j = 0; j < this->getDimension(); j++) {
      tileComponents[j] = this->_paramToGridValue(parameters[j], i, j);
    }

// Add a unique number_tiling identifier.
    tileComponents[this->getDimension()] = i;

    AI::Algorithm::Hash::SuperFastHash hashAlg;
    AI::UINT hashVal = hashAlg.hash(
        (AI::BYTE*) &tileComponents[0],
        tileComponents.size() * sizeof(tileComponents[0]));
    
    fv.push_back(hashVal % this->_sizeCache);
  }

  return fv;
}

} // namespace SL
} /* namespace Algorithm */
} /* namespace AI */

#endif /* TileCode */
