/*
 * TileCodeMurMur.h
 *
 *  Created on: Jun 15, 2014
 *      Author: jandres
 */

#ifndef TILECODEMURMUR_H_
#define TILECODEMURMUR_H_

#include "TileCode.h"
#include "HashMurmur3.h"

namespace AI {
namespace Algorithm {
namespace SL {

/*! \class TileCodeMurMur
 *  \brief Tile Code using MurMur3 hash.
 */
class TileCodeMurMur : public TileCode {
 public:
  TileCodeMurMur(vector<DimensionInfo<FLOAT> > dimensionalInfos,
                 size_t numTilings);

  TileCodeMurMur(vector<DimensionInfo<FLOAT> > dimensionalInfos,
                 size_t numTilings, size_t sizeHint);

  virtual void getFeatureVector(const STATE_CONT& parameters,
                                FEATURE_VECTOR& fv);
};

inline TileCodeMurMur::TileCodeMurMur(
    vector<DimensionInfo<FLOAT> > dimensionalInfos, size_t numTilings)
    : TileCode(dimensionalInfos, numTilings) {
}

inline TileCodeMurMur::TileCodeMurMur(
    vector<DimensionInfo<FLOAT> > dimensionalInfos, size_t numTilings,
    size_t sizeHint)
    : TileCode(dimensionalInfos, numTilings) {
  if (sizeHint > this->_sizeCache) {
    this->_sizeCache = 3001;
  }
}

inline void TileCodeMurMur::getFeatureVector(
    const STATE_CONT& parameters, FEATURE_VECTOR& tilings) {
  assert(this->getDimension() == parameters.size());

  vector<AI::INT> tileComponents(this->getDimension() + 1);
  for (AI::INT i = 0; i < this->_numTilings; i++) {
    for (size_t j = 0; j < this->getDimension(); j++) {
      tileComponents[j] = this->_paramToGridValue(parameters[j], i, j);
    }

    // Add a unique number_tiling identifier.
    tileComponents[this->getDimension()] = i;

    AI::Algorithm::Hash::Murmur3 _hashAlg;
    AI::Algorithm::Hash::HashMurmur3Out hash = _hashAlg.hash(
        (AI::BYTE*) tileComponents.data(),
        tileComponents.size() * sizeof(AI::INT));
    //AI::Algorithm::getHashVal(tileComponents, hash);

    tilings.push_back(hash.hashVal[0] % this->_sizeCache);
  }
}

} // namespace SL
} /* namespace Algorithm */
} /* namespace AI */

#endif /* TILECODEMURMUR_H_ */
