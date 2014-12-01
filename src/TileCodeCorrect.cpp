/**
 * TileCorrect.cpp
 */

#include "TileCodeCorrect.h"

namespace AI {
namespace Algorithm {
namespace SL {

TileCodeCorrect::TileCodeCorrect(vector<DimensionInfo<FLOAT> >& dimensionalInfos,
                                        size_t numTilings)
    : TileCode(dimensionalInfos, numTilings) {
}

FEATURE_VECTOR TileCodeCorrect::getFeatureVector(
    const STATE_CONT& parameters) {
  assert(this->getDimension() == parameters.size());  
  FEATURE_VECTOR fv;
  fv.resize(this->_numTilings);
  
  for (AI::INT i = 0; i < this->_numTilings; i++) {
    // x1 + x2*x1.gridSize + x3*x1.gridSize*x2.gridSize + ...
    size_t hashedIndex = 0;
    size_t mult = 1;
    for (size_t j = 0; j < this->getDimension(); j++) {
      hashedIndex += this->_paramToGridValue(parameters[j], i, j) * mult;
      mult *= this->_dimensionalInfos[j].GetGridCountReal();
    }

    hashedIndex += mult * i;
    fv[i] = hashedIndex;
  }
  return fv;
}

} // namespace SL
} // namespace Algorithm
} // namespace AI
