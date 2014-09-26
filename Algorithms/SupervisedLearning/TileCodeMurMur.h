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
	class TileCodeMurMur: public TileCode {
	public:
	  TileCodeMurMur(vector<DimensionInfo<FLOAT> > dimensionalInfos,
		  size_t numTilings);

	  TileCodeMurMur(vector<DimensionInfo<FLOAT> > dimensionalInfos,
		  size_t numTilings, size_t sizeHint);

	  /**
	   * Hashed the parameter in Real space to a Natural space [0, infinity).
	   * @param parameters
	   * @return Vector of discretize index.
	   */
	  virtual void getFeatureVector(const STATE_CONT& parameters,
		  FEATURE_VECTOR& fv);
	};

  } /* namespace Algorithm */
} /* namespace AI */

inline AI::Algorithm::TileCodeMurMur::TileCodeMurMur(
	vector<DimensionInfo<FLOAT> > dimensionalInfos, size_t numTilings) :
		TileCode(dimensionalInfos, numTilings) {
}

inline AI::Algorithm::TileCodeMurMur::TileCodeMurMur(
	vector<DimensionInfo<FLOAT> > dimensionalInfos, size_t numTilings,
	size_t sizeHint) :
		TileCode(dimensionalInfos, numTilings) {
  if (sizeHint > this->_sizeCache) {
	this->_sizeCache = 3001;
  }
}

inline void AI::Algorithm::TileCodeMurMur::getFeatureVector(
	const STATE_CONT& parameters, FEATURE_VECTOR& tilings) {
  assert(this->_dimension == parameters.size());

  vector<AI::INT> tileComponents(this->_dimension + 1);
  for (AI::INT i = 0; i < this->_numTilings; i++) {
	for (size_t j = 0; j < this->_dimension; j++) {
	  tileComponents[j] = this->_paramToGridValue(parameters[j], i, j);
	}

	// Add a unique number_tiling identifier.
	tileComponents[this->_dimension] = i;

	AI::HashMurmur3Out hash;
	AI::getHashVal(tileComponents, hash);

	tilings.push_back(hash.hashVal[0] % this->_sizeCache);
  }
}

#endif /* TILECODEMURMUR_H_ */
