//
// Created by jandres on 15/11/16.
//

#include <random>

#include "coding/TileCodeUNH.h"
#include "hash/HashUNH.h"

namespace rl {
namespace coding {

TileCodeUNH::TileCodeUNH(
  vector<DimensionInfo<FLOAT> > dimensionalInfos, size_t numTilings)
  : TileCode(dimensionalInfos, numTilings) {
  _normalization = vector<rl::FLOAT>(this->getDimension());

  for (size_t i = 0; i < this->_dimensionalInfos.size(); i++) {
    _normalization[i] = this->_numTilings
      / this->_dimensionalInfos[i].GetRangeDifference();
  }
}

TileCodeUNH::TileCodeUNH(
  vector<DimensionInfo<FLOAT> > dimensionalInfos, size_t numTilings,
  size_t sizeHint)
  : TileCode(dimensionalInfos, numTilings) {
  if (sizeHint > this->_sizeCache) {
    this->_sizeCache = sizeHint;
  }

  _normalization = vector<rl::FLOAT>(this->getDimension());

  for (size_t i = 0; i < this->_dimensionalInfos.size(); i++) {
    _normalization[i] = this->_numTilings
      / this->_dimensionalInfos[i].GetRangeDifference();
  }

}

FEATURE_VECTOR TileCodeUNH::getFeatureVector(
  const STATE_CONT& parameters) {
  assert(this->getDimension() == parameters.size());
  FEATURE_VECTOR fv;

  vector<rl::UINT> base(this->getDimension(), 0);
  vector<rl::INT> qStates(this->getDimension());
  for (size_t i = 0; i < this->getDimension(); i++) {
    // Note to floor since casting to integer is not consistent
    // with negative number. Casting is always a number toward zero.
    qStates[i] = floor(parameters[i] * _normalization[i]);
  }

  for (size_t i = 0; i < this->_numTilings; i++) {
    vector<rl::INT> tileComponents(this->getDimension() + 1);

    for (size_t j = 0; j < this->getDimension(); j++) {
      tileComponents[j] = qStates[j]
        - mod(qStates[j] - base[j], this->_numTilings);
      base[j] += 1 + (j * 2);
    }
    tileComponents[this->getDimension()] = i;
    hash::UNH hashAlg;
    fv.push_back(
      hashAlg.hash((rl::BYTE*) &tileComponents[0], this->_sizeCache));
  }

  return fv;
}

} // namespace Coding
} /* namespace rl */
