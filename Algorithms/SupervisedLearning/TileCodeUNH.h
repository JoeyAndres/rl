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
  virtual void getFeatureVector(const STATE_CONT& parameters,
                                FEATURE_VECTOR& fv);

  size_t mod(size_t n, size_t k) {
    return (n >= 0) ? n % k : k - 1 - ((-n - 1) % k);
  }

 protected:

 protected:
  // Optimization parameters.
  vector<AI::FLOAT> _normalization;
};

} /* namespace Algorithm */
} /* namespace AI */

inline AI::Algorithm::TileCodeUNH::TileCodeUNH(
    vector<DimensionInfo<FLOAT> > dimensionalInfos, size_t numTilings)
    : TileCode(dimensionalInfos, numTilings) {
  _normalization = vector < AI::FLOAT > (this->_dimension);

  for (size_t i = 0; i < this->_dimensionalInfos.size(); i++) {
    _normalization[i] = this->_numTilings
        / this->_dimensionalInfos[i].GetRangeDifference();
  }
}

inline AI::Algorithm::TileCodeUNH::TileCodeUNH(
    vector<DimensionInfo<FLOAT> > dimensionalInfos, size_t numTilings,
    size_t sizeHint)
    : TileCode(dimensionalInfos, numTilings) {
  if (sizeHint > this->_sizeCache) {
    this->_sizeCache = sizeHint;
  }

  _normalization = vector < AI::FLOAT > (this->_dimension);

  for (size_t i = 0; i < this->_dimensionalInfos.size(); i++) {
    _normalization[i] = this->_numTilings
        / this->_dimensionalInfos[i].GetRangeDifference();
  }

}

inline void AI::Algorithm::TileCodeUNH::getFeatureVector(
    const STATE_CONT& parameters, FEATURE_VECTOR& tilings) {
  assert(this->_dimension == parameters.size());

  vector<AI::UINT> base(this->_dimension, 0);
  vector<AI::INT> qStates(this->_dimension);
  for (size_t i = 0; i < this->_dimension; i++) {
    // Note to floor since casting to integer is not consistent
    // with negative number. Casting is always a number toward zero.
    qStates[i] = floor(parameters[i] * _normalization[i]);
  }

  for (size_t i = 0; i < this->_numTilings; i++) {
    vector<AI::INT> tileComponents(this->_dimension + 1);

    for (size_t j = 0; j < this->_dimension; j++) {
      tileComponents[j] = qStates[j]
          - mod(qStates[j] - base[j], this->_numTilings);
      base[j] += 1 + (j * 2);
    }
    tileComponents[this->_dimension] = i;
    AI::Algorithm::Hash::UNH hashAlg;
    tilings.push_back(hashAlg.hash((AI::BYTE*)&tileComponents[0], this->_sizeCache));
  }
}

#endif /* TILECODEUNH_H_ */
