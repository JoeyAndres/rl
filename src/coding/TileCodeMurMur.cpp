/**
 * TilecodeMurMur.cpp 
 */

#include "coding/TileCodeMurMur.h"
#include "hash/HashMurmur3.h"

namespace rl {
namespace coding {

TileCodeMurMur::TileCodeMurMur(vector<DimensionInfo<FLOAT> >& dimensionalInfos,
                                      size_t numTilings)
    : TileCode(dimensionalInfos, numTilings) {
}

TileCodeMurMur::TileCodeMurMur(
  vector<DimensionInfo<FLOAT> >& dimensionalInfos,
  size_t numTilings,
  size_t sizeHint)
  : TileCode(dimensionalInfos, numTilings) {
  this->_sizeCache = sizeHint;
}

FEATURE_VECTOR TileCodeMurMur::getFeatureVector(
    const STATE_CONT& parameters) {
  assert(this->getDimension() == parameters.size());
  FEATURE_VECTOR fv;

  vector<rl::INT> tileComponents(this->getDimension() + 1);
  for (rl::INT i = 0; i < this->_numTilings; i++) {
    for (size_t j = 0; j < this->getDimension(); j++) {
      tileComponents[j] = this->paramToGridValue(parameters[j], i, j);
    }
    
    // Add a unique number_tiling identifier.
    tileComponents[this->getDimension()] = i;

    hash::Murmur3 _hashAlg;
    hash::HashMurmur3Out hash = _hashAlg.hash(
        (rl::BYTE*) tileComponents.data(),
        tileComponents.size() * sizeof(rl::INT));

    fv.push_back(hash.hashVal[0] % this->_sizeCache);
  }
  
  return fv;
}

} // namespace Coding
} // namespace rl
