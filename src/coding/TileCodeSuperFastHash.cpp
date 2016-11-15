//
// Created by jandres on 15/11/16.
//

#include "coding/TileCodeSuperFastHash.h"
#include "hash/HashSuperFastHash.h"

namespace rl {
namespace coding {

TileCodeSuperFastHash::TileCodeSuperFastHash(vector<DimensionInfo<FLOAT> >& dimensionalInfos,
                                                    size_t numTilings)
  : TileCode(dimensionalInfos, numTilings) {
}

TileCodeSuperFastHash::TileCodeSuperFastHash(vector<DimensionInfo<FLOAT> >& dimensionalInfos,
                                                    size_t numTilings,
                                                    size_t sizeHint)
  : TileCode(dimensionalInfos, numTilings) {
  if (sizeHint > this->_sizeCache) {
    this->_sizeCache = sizeHint;
  }
}

FEATURE_VECTOR TileCodeSuperFastHash::getFeatureVector(
  const STATE_CONT& parameters) {
  vector<rl::INT> tileComponents(this->getDimension() + 1);
  FEATURE_VECTOR fv;

  for (size_t i = 0; i < this->_numTilings; i++) {
    for (size_t j = 0; j < this->getDimension(); j++) {
      tileComponents[j] = this->paramToGridValue(parameters[j], i, j);
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

} // namespace Coding
} /* namespace rl */
