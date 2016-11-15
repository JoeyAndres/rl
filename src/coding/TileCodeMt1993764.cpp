/**
 * TileCodeMt1993764.cpp
 */

#include "coding/TileCodeMt1993764.h"

namespace rl {
namespace coding {

TileCodeMt1993764::TileCodeMt1993764(
    vector<DimensionInfo<FLOAT> >& dimensionalInfos, size_t numTilings)
    : TileCode(dimensionalInfos, numTilings) {
}

TileCodeMt1993764::TileCodeMt1993764(
    vector<DimensionInfo<FLOAT> >& dimensionalInfos, size_t numTilings,
    size_t sizeHint)
    : TileCode(dimensionalInfos, numTilings) {
  if (sizeHint > this->_sizeCache) {
    this->_sizeCache = sizeHint;
  }
}

FEATURE_VECTOR TileCodeMt1993764::getFeatureVector(
    const STATE_CONT& parameters) {
  vector<rl::INT> tileComponents(this->getDimension() + 1);
  FEATURE_VECTOR fv;
  
  for (size_t i = 0; i < this->_numTilings; i++) {
    for (size_t j = 0; j < this->getDimension(); j++) {
      tileComponents[j] = this->paramToGridValue(parameters[j], i, j);
    }

    // Add a unique number_tiling identifier.
    tileComponents[this->getDimension()] = i;

    std::seed_seq seed1(tileComponents.begin(), tileComponents.end());
    _prng.seed(seed1);

    fv.push_back(_prng() % this->_sizeCache);
  }

  return fv;
}

} // namespace Coding
} /* namespace rl */
