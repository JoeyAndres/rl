/**
 * TileCode.cpp
 */

#include "coding/TileCode.h"

namespace rl {
namespace coding {

TileCode::TileCode(vector<DimensionInfo<FLOAT> >& dimensionalInfos,
                   size_t numTilings) : _dimensionalInfos(dimensionalInfos){
  assert(numTilings > 0);  
  _numTilings = numTilings;

  // Calculate the size.
  _sizeCache = _calculateSizeCache();

  // Calculate random offsets.
  std::uniform_real_distribution<rl::FLOAT> distribution(0, 1.0F);
  for (size_t i = 0; i < _numTilings; i++) {
    _randomOffsets.push_back(vector<rl::FLOAT>());
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
  rl::UINT size = 1;
  for (const DimensionInfo<FLOAT>& di : _dimensionalInfos) {
    size *= di.GetGridCountReal();
  }

  size *= _numTilings;

  // Add paddings
#ifdef MMX
  // MMX is 64bits, same as rl::DOUBLE.
#elif defined(SSE) || defined(SSE2) || defined(SSE3) || defined(SSE4) || defined(SSE4_1) || defined(SSE4_2) || defined(SSE4A)
  size += size%2;
#elif AVX
  size += size%4;
#elif NO_INTRINSIC
#endif
  return size;
}

size_t TileCode::paramToGridValue(rl::FLOAT param, size_t tilingIndex, size_t dimensionIndex) {
  auto randomOffset = _randomOffsets[tilingIndex][dimensionIndex];
  auto dimGeneraliztionScale = this->_dimensionalInfos[dimensionIndex].getGeneralizationScale();
  auto dimLowerBound = this->_dimensionalInfos[dimensionIndex].getLowerBound();
  auto dimGridCountIdeal = this->_dimensionalInfos[dimensionIndex].GetGridCountIdeal();
  auto dimRangeMagnitude = this->_dimensionalInfos[dimensionIndex].GetRangeDifference();

  return (
    (param + randomOffset * dimGeneraliztionScale - dimLowerBound) * dimGridCountIdeal
  ) / dimRangeMagnitude;
}

}  // namespace Coding
}  // namespace rl
