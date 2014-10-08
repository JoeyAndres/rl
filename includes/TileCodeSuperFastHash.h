/*
 * TileCode
 *
 *  Created on: Jun 18, 2014
 *      Author: jandres
 */

#ifndef TILECODESUPERFASTHASH_H_
#define TILECODESUPERFASTHASH_H_

#include "TileCode.h"
#include "HashSuperFastHash.h"
#include "xxhash.h"

namespace AI {
namespace Algorithm {
/**
 * TileCoding with Superfast hash.
 * Superfast hash created by Paul Hsieh.
 */
class TileCodeSuperFastHash: public TileCode {
public:
	/**
	 * @param dimensionalInfos
	 * @param numTilings
	 */
	TileCodeSuperFastHash(vector<DimensionInfo<FLOAT> > dimensionalInfos,
			size_t numTilings);

	/**
	 * @param dimensionalInfos
	 * @param numTilings
	 * @param sizeHint If sizeHint is greater than calculated size, then sizeHint
	 * will be used instead. The bigger the sizeHint, the less likely is the collision
	 * during hashing.
	 */
	TileCodeSuperFastHash(vector<DimensionInfo<FLOAT> > dimensionalInfos,
			size_t numTilings, size_t sizeHint);

	/**
	 * Hashed the parameter in Real space to a Natural space [0, infinity).
	 * @param parameters
	 * @return Vector of discretize index.
	 */
	virtual void getFeatureVector(const STATE_CONT& parameters,
			FEATURE_VECTOR& fv);
};

}
/* namespace Algorithm */
} /* namespace AI */

inline AI::Algorithm::TileCodeSuperFastHash::TileCodeSuperFastHash(
		vector<DimensionInfo<FLOAT> > dimensionalInfos, size_t numTilings) :
		TileCode(dimensionalInfos, numTilings) {
}

inline AI::Algorithm::TileCodeSuperFastHash::TileCodeSuperFastHash(
		vector<DimensionInfo<FLOAT> > dimensionalInfos, size_t numTilings,
		size_t sizeHint) :
		TileCode(dimensionalInfos, numTilings) {
	if (sizeHint > this->_sizeCache) {
		this->_sizeCache = sizeHint;
	}
}

inline void AI::Algorithm::TileCodeSuperFastHash::getFeatureVector(
		const STATE_CONT& parameters, FEATURE_VECTOR& tilings) {
	vector<AI::INT> tileComponents(this->_dimension + 1);
	for (size_t i = 0; i < this->_numTilings; i++) {
		for (size_t j = 0; j < this->_dimension; j++) {
			tileComponents[j] = this->_paramToGridValue(parameters[j], i, j);
		}

// Add a unique number_tiling identifier.
		tileComponents[this->_dimension] = i;

		AI::UINT hashVal = AI::SuperFastHash((char*) &tileComponents[0],
				tileComponents.size() * sizeof(tileComponents[0]));
		tilings.push_back(hashVal % this->_sizeCache);
	}
}

#endif /* TileCode */
