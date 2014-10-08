/*
 * TileCodeCorrect.h
 *
 *  Created on: Jun 15, 2014
 *      Author: jandres
 */

#ifndef TILECODECORRECT_H_
#define TILECODECORRECT_H_

#include <vector>
#include <random>
#include <cmath>

#include "TileCode.h"

using namespace std;

namespace AI {
namespace Algorithm {
class TileCodeCorrect: public TileCode {
public:
	/**
	 * @param dimensionalInfos A vector dimensionalInfos.
	 * @param numTilings The higher the value, the more accurate is the
	 * 			generalization.
	 */
	TileCodeCorrect(vector<DimensionInfo<FLOAT> > dimensionalInfos,
			size_t numTilings);

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

inline AI::Algorithm::TileCodeCorrect::TileCodeCorrect(
		vector<DimensionInfo<FLOAT> > dimensionalInfos, size_t numTilings) :
		TileCode(dimensionalInfos, numTilings) {
}

inline void AI::Algorithm::TileCodeCorrect::getFeatureVector(
		const STATE_CONT& parameters, FEATURE_VECTOR& tilings) {
	assert(this->_dimension == parameters.size());

	vector<AI::INT> tileComponents(this->_dimension + 1);
	for (AI::INT i = 0; i < this->_numTilings; i++) {
		for (size_t j = 0; j < this->_dimension; j++) {
			tileComponents[j] = this->_paramToGridValue(parameters[j], i, j);
		}

		// x1 + x2*x1.gridSize + x3*x1.gridSize*x2.gridSize + ...
		size_t hashedIndex = 0;
		size_t tileComponentMultiplier = 1;
		for (size_t j = 0; j < this->_dimension; j++) {
			hashedIndex += tileComponents[j] * tileComponentMultiplier;
			tileComponentMultiplier *=
					this->_dimensionalInfos[j].GetGridCountReal();
		}

		hashedIndex += tileComponentMultiplier * i;

		tilings.push_back(hashedIndex);
	}
}

#endif /* TILECODECORRECT_H_ */
