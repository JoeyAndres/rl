/*
 * TileCodeMt1993764.h
 *
 *  Created on: Jun 18, 2014
 *      Author: jandres
 */

#ifndef TIleCODEMT1993764_H_
#define TIleCODEMT1993764_H_

#include <random>

#include "TileCode.h"

namespace AI {
namespace Algorithm {

/*! \class TileCodeMt1993764
 *  \brief Tile Code using Mt1993764 hash.2
 */
class TileCodeMt1993764 : public TileCode {
 public:
  /**
   * @param dimensionalInfos
   * @param numTilings
   */
  TileCodeMt1993764(vector<DimensionInfo<FLOAT> > dimensionalInfos,
                    size_t numTilings);

  /**
   * @param dimensionalInfos
   * @param numTilings
   * @param sizeHint If sizeHint is greater than calculated size, then sizeHint
   * will be used instead. The bigger the sizeHint, the less likely is the collision
   * during hashing.
   */
  TileCodeMt1993764(vector<DimensionInfo<FLOAT> > dimensionalInfos,
                    size_t numTilings, size_t sizeHint);

  /**
   * Hashed the parameter in Real space to a Natural space [0, infinity).
   * @param parameters
   * @return Vector of discretize index.
   */
  virtual void getFeatureVector(const STATE_CONT& parameters,
                                FEATURE_VECTOR& fv);

 protected:
  std::mt19937_64 _prng;
};

} /* namespace Algorithm */
} /* namespace AI */

inline AI::Algorithm::TileCodeMt1993764::TileCodeMt1993764(
    vector<DimensionInfo<FLOAT> > dimensionalInfos, size_t numTilings)
    : TileCode(dimensionalInfos, numTilings) {
}

inline AI::Algorithm::TileCodeMt1993764::TileCodeMt1993764(
    vector<DimensionInfo<FLOAT> > dimensionalInfos, size_t numTilings,
    size_t sizeHint)
    : TileCode(dimensionalInfos, numTilings) {
  if (sizeHint > this->_sizeCache) {
    this->_sizeCache = sizeHint;
  }
}

inline void AI::Algorithm::TileCodeMt1993764::getFeatureVector(
    const STATE_CONT& parameters, FEATURE_VECTOR& tilings) {
  vector<AI::INT> tileComponents(this->_dimension + 1);
  for (size_t i = 0; i < this->_numTilings; i++) {
    for (size_t j = 0; j < this->_dimension; j++) {
      tileComponents[j] = this->_paramToGridValue(parameters[j], i, j);
    }

// Add a unique number_tiling identifier.
    tileComponents[this->_dimension] = i;

    std::seed_seq seed1(tileComponents.begin(), tileComponents.end());
    _prng.seed(seed1);

    tilings.push_back(_prng() % this->_sizeCache);
  }
}

#endif // TIleCODEMT1993764_H_
