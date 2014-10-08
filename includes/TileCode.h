/* 
 * File:   TileCode.h
 * Author: jandres
 *
 * Created on June 8, 2014, 8:28 AM
 */

#ifndef TILECODE_H
#define	TILECODE_H

#include "GlobalHeader.h"  // Removes assertions.

#include <cstdint>
#include <iostream>
#include <random>
#include <stdarg.h>
#include <vector>
#include <cassert>
#include <cmath>

#include "DimensionInfo.h"

using namespace std;

namespace AI {
namespace Algorithm {

class TileCode {
public:
	/**
	 * @param dimensionalInfos A vector dimensionalInfos.
	 * @param numTilings The higher the value, the more accurate is the
	 * 			generalization.
	 */
	TileCode(vector<DimensionInfo<FLOAT> > dimensionalInfos, size_t numTilings);

	/**
	 * Hashed the parameter in Real space to a Natural space [0, infinity).
	 * @param parameters
	 * @return Vector of discretize index.
	 */
	virtual void getFeatureVector(const STATE_CONT& parameters,
			FEATURE_VECTOR& fv) = 0;

	/**
	 * @return size of the weight vector.
	 */
	size_t getSize() const;

	/**
	 * @param numTilings
	 */
	void setNumTilings(size_t numTilings);

	/**
	 * @return number of tilings.
	 */
	size_t getNumTilings() const;

	/**
	 * @param dimension
	 */
	//void setDimension(size_t dimension);
	/**
	 * @return number of dimension.
	 */
	size_t getDimension() const;

public:
	// Static functions.
	static void displayGnuPlot(const TileCode& tileCode);
protected:
	size_t _calculateSizeCache();
	size_t _paramToGridValue(AI::FLOAT param, size_t tilingIndex,
			size_t dimensionIndex);

protected:
	size_t _dimension;
	size_t _numTilings;
	vector<DimensionInfo<FLOAT> > _dimensionalInfos;
	std::random_device _randomDevice;
	std::default_random_engine _pseudoRNG;

	// This implementation is in response to massive performance drop due
	// unnecessary recalculation of size. Note to update this when possible.
	size_t _sizeCache;

	// To avoid recalculating randomness, this aid the consistency of sample.
	// One might say, that its not a real sample if the offsets are precomputed,
	// and he is right. The problem though is that doing it randomly(pseudo or otherwise)
	// would require ALOT more #tilings to achieve consistency. This alleviates us from
	// that problem and still have a reasonable generalization.
	vector<vector<AI::FLOAT> > _randomOffsets;
};

TileCode::TileCode(vector<DimensionInfo<FLOAT> > dimensionalInfos,
		size_t numTilings) {
	assert(numTilings > 0);

	_dimensionalInfos = dimensionalInfos;
	_dimension = dimensionalInfos.size();
	_numTilings = numTilings;

	// Calculate the size.
	_sizeCache = _calculateSizeCache();

	// Calculate random offsets.
	std::uniform_real_distribution<AI::FLOAT> distribution(0, 1.0F);
	for (size_t i = 0; i < _numTilings; i++) {
		_randomOffsets.push_back(vector<AI::FLOAT>());
		for (size_t j = 0; j < _dimension; j++) {
			_randomOffsets[i].push_back(
					distribution(_pseudoRNG) * _dimensionalInfos[j].GetOffsets()
							* _dimensionalInfos[j].getGeneralizationScale());
		}
	}
}

void TileCode::setNumTilings(size_t numTilings) {
	this->_numTilings = numTilings;
}

size_t TileCode::getNumTilings() const {
	return _numTilings;
}

size_t TileCode::getDimension() const {
	return _dimension;
}

size_t TileCode::getSize() const {
	return _sizeCache;
}

size_t TileCode::_calculateSizeCache() {
	// Calculate the size.
	AI::UINT size = 1;
	for (const DimensionInfo<FLOAT>& di : _dimensionalInfos) {
		size *= di.GetGridCountReal();
	}
	size *= _numTilings;
	return size;
}

}
}

inline size_t AI::Algorithm::TileCode::_paramToGridValue(AI::FLOAT param,
		size_t tilingIndex, size_t dimensionIndex) {
	return ((param
			+ _randomOffsets[tilingIndex][dimensionIndex]
					* this->_dimensionalInfos[dimensionIndex].getGeneralizationScale()
			- this->_dimensionalInfos[dimensionIndex].getLowerBound())
			* this->_dimensionalInfos[dimensionIndex].GetGridCountIdeal())
			/ this->_dimensionalInfos[dimensionIndex].GetRangeDifference();
}

#endif	/* TILECODE_H */
