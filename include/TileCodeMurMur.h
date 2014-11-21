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
  TileCodeMurMur(vector<DimensionInfo<FLOAT> >& dimensionalInfos,
                 size_t numTilings);

  TileCodeMurMur(vector<DimensionInfo<FLOAT> >& dimensionalInfos,
                 size_t numTilings, size_t sizeHint);

  virtual FEATURE_VECTOR getFeatureVector(const STATE_CONT& parameters);
};

inline TileCodeMurMur::TileCodeMurMur(vector<DimensionInfo<FLOAT> >& dimensionalInfos,
                                      size_t numTilings)
    : TileCode(dimensionalInfos, numTilings) {
}

inline TileCodeMurMur::TileCodeMurMur(vector<DimensionInfo<FLOAT> >& dimensionalInfos,
                                      size_t numTilings,
    size_t sizeHint)
    : TileCode(dimensionalInfos, numTilings) {
  if (sizeHint > this->_sizeCache) {
    this->_sizeCache = 3001;
  }
}

inline FEATURE_VECTOR TileCodeMurMur::getFeatureVector(
    const STATE_CONT& parameters) {
  assert(this->getDimension() == parameters.size());
  FEATURE_VECTOR fv;

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

    fv.push_back(hash.hashVal[0] % this->_sizeCache);
  }
  
  return fv;
}

} // namespace SL
} /* namespace Algorithm */
} /* namespace AI */

#endif /* TILECODEMURMUR_H_ */
