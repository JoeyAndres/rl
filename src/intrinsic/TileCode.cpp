/**
 * TileCode.cpp
 */

#include "TileCode.h"


namespace AI {
namespace Algorithm {
namespace SL {

TileCode::TileCode(vector<DimensionInfo<FLOAT> >& dimensionalInfos,
                   size_t numTilings) : _dimensionalInfos(dimensionalInfos){
  assert(numTilings > 0);  
  _numTilings = numTilings;

  // Calculate the size.
  _sizeCache = _calculateSizeCache();

  // Calculate random offsets.
  std::uniform_real_distribution<AI::FLOAT> distribution(0, 1.0F);
  for (size_t i = 0; i < _numTilings; i++) {
    _randomOffsets.push_back(vector<AI::FLOAT>());
    for (size_t j = 0; j < this->getDimension(); j++) {
      _randomOffsets[i].push_back(
          distribution(_pseudoRNG) * _dimensionalInfos[j].GetOffsets()
          * _dimensionalInfos[j].getGeneralizationScale());
    }
  }
}

void TileCode::setNumTilings(size_t numTilings) {
  this->_numTilings = numTilings;

  // Update size cache.
  _sizeCache = _calculateSizeCache();
}

size_t TileCode::getNumTilings() const {
  return _numTilings;
}

size_t TileCode::getDimension() const {
  return _dimensionalInfos.size();
}

size_t TileCode::getSize() const {
  return _sizeCache;
}

size_t TileCode::_calculateSizeCache() {
  // Calculate the size.
  AI::UINT size = 1;
  for (const DimensionInfo<FLOAT>& di : _dimensionalInfos) {
    size *= di.GetGridCountReal();
  }
  size *= _numTilings;
  if(size % 2 == 0)
    return size;
  else
    return size+1;
}

size_t TileCode::_paramToGridValue(
    AI::FLOAT param, size_t tilingIndex, size_t dimensionIndex) {
  return ((param +
           _randomOffsets[tilingIndex][dimensionIndex] * this->_dimensionalInfos[dimensionIndex].getGeneralizationScale() -
           this->_dimensionalInfos[dimensionIndex].getLowerBound()) * this->_dimensionalInfos[dimensionIndex].GetGridCountIdeal())
           / this->_dimensionalInfos[dimensionIndex].GetRangeDifference();
}

}  // namespace SL
}  // namespace Algorithm
}  // namespace AI
