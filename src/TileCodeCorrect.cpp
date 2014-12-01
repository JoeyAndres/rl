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
  for(UINT i = 0; i < this->_numTilings; i++){
    int mult = 1;
    _tileComponentMultiplier.push_back(vector<UINT>());
    for(UINT j = 0; j < this->getDimension(); j++){
      _tileComponentMultiplier[i].push_back(mult*(i+1));
      mult *= this->_dimensionalInfos[j].GetGridCountReal();
    }
  }
}

FEATURE_VECTOR TileCodeCorrect::getFeatureVector(
    const STATE_CONT& parameters) {
  assert(this->getDimension() == parameters.size());  
  FEATURE_VECTOR fv;
  fv.resize(this->_numTilings);
  
  for (AI::INT i = 0; i < this->_numTilings; i++) {
    // x1 + x2*x1.gridSize + x3*x1.gridSize*x2.gridSize + ...
    size_t hashedIndex = 0;
    for (size_t j = 0; j < this->getDimension(); j++) {
      hashedIndex += this->_paramToGridValue(parameters[j], i, j) * _tileComponentMultiplier[0][j];
    }

    hashedIndex += _tileComponentMultiplier[i][this->getDimension()-1];
    fv[i] = (hashedIndex);
  }
  return fv;
}
} // namespace SL
} // namespace Algorithm
} // namespace AI
