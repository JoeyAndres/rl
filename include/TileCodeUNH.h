/*
 * TileCodeUNH.h
 *
 *  Created on: Jun 15, 2014
 *      Author: jandres
 */

#ifndef TILECODUNH_H_
#define TILECODUNH_H_

#include <random>

#include "TileCode.h"
#include "HashUNH.h"

namespace AI {
namespace Algorithm {
namespace SL {

/*! \class TileCodeUNH
 *  \brief Tile Code using University New Hampshire hash, or UNH.
 */
class TileCodeUNH : public TileCode {
 public:
  TileCodeUNH(vector<DimensionInfo<FLOAT> > dimensionalInfos,
              size_t numTilings);

  TileCodeUNH(vector<DimensionInfo<FLOAT> > dimensionalInfos, size_t numTilings,
              size_t sizeHint);

  /**
   * Hashed the parameter in Real space to a Natural space [0, infinity).
   * @param parameters
   * @return Vector of discretize index.
   */
  virtual FEATURE_VECTOR getFeatureVector(const STATE_CONT& parameters);

  size_t mod(size_t n, size_t k) {
    return (n >= 0) ? n % k : k - 1 - ((-n - 1) % k);
  }

 protected:
  // Optimization parameters.
  vector<AI::FLOAT> _normalization;
};

TileCodeUNH::TileCodeUNH(
    vector<DimensionInfo<FLOAT> > dimensionalInfos, size_t numTilings)
    : TileCode(dimensionalInfos, numTilings) {
  _normalization = vector<AI::FLOAT>(this->getDimension());

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

  _normalization = vector<AI::FLOAT>(this->getDimension());

  for (size_t i = 0; i < this->_dimensionalInfos.size(); i++) {
    _normalization[i] = this->_numTilings
        / this->_dimensionalInfos[i].GetRangeDifference();
  }

}

FEATURE_VECTOR TileCodeUNH::getFeatureVector(
    const STATE_CONT& parameters) {
  assert(this->getDimension() == parameters.size());
  FEATURE_VECTOR fv;

  vector<AI::UINT> base(this->getDimension(), 0);
  vector<AI::INT> qStates(this->getDimension());
  for (size_t i = 0; i < this->getDimension(); i++) {
    // Note to floor since casting to integer is not consistent
    // with negative number. Casting is always a number toward zero.
    qStates[i] = floor(parameters[i] * _normalization[i]);
  }

  for (size_t i = 0; i < this->_numTilings; i++) {
    vector<AI::INT> tileComponents(this->getDimension() + 1);

    for (size_t j = 0; j < this->getDimension(); j++) {
      tileComponents[j] = qStates[j]
          - mod(qStates[j] - base[j], this->_numTilings);
      base[j] += 1 + (j * 2);
    }
    tileComponents[this->getDimension()] = i;
    AI::Algorithm::Hash::UNH hashAlg;
    fv.push_back(
        hashAlg.hash((AI::BYTE*) &tileComponents[0], this->_sizeCache));
  }

  return fv;
}

} // namespace SL
} /* namespace Algorithm */
} /* namespace AI */

#endif /* TILECODEUNH_H_ */
