/**
 * TileCorrect.cpp
 */

#include "coding/TileCodeCorrect.h"

namespace rl {
namespace coding {

TileCodeCorrect::TileCodeCorrect(vector<DimensionInfo<FLOAT> >& dimensionalInfos,
                                        size_t numTilings)
    : TileCode(dimensionalInfos, numTilings) {
}

FEATURE_VECTOR TileCodeCorrect::getFeatureVector(
    const STATE_CONT& parameters) {
  assert(this->getDimension() == parameters.size());  
  FEATURE_VECTOR fv;
  fv.resize(this->_numTilings);
  
  for (rl::INT i = 0; i < this->_numTilings; i++) {
    // x1 + x2*x1.gridSize + x3*x1.gridSize*x2.gridSize + ...
    rl::INT hashedIndex = 0;
    rl::INT mult = 1;
    for (size_t j = 0; j < this->getDimension(); j++) {
      hashedIndex += this->paramToGridValue(parameters[j], i, j) * mult;
      mult *= this->_dimensionalInfos[j].GetGridCountReal();
    }

    hashedIndex += mult * i;
    assert(hashedIndex <= this->_sizeCache /* Size cache exceeded. Illegal feature vector value. */);
    fv[i] = hashedIndex;
  }
  return fv;
}

} // namespace Coding
} // namespace rl
