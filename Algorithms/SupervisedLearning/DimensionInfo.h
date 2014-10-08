/* 
 * File:   DimensionInfo.h
 * Author: jandres
 *
 * Created on June 9, 2014, 2:24 PM
 */

#ifndef DIMENSIONINFO_H
#define	DIMENSIONINFO_H

#include "GlobalHeader.h"

#include <map>
#include <cmath>

using namespace std;

namespace AI {
namespace Algorithm {

template<typename D = AI::FLOAT>
class DimensionInfo {
public:
	/**
	 * DimensionInfo consist of range [a, b] and gridCount. Higher
	 * grid count means more precision, less grid count means more
	 * generalization.
	 * @param lowerRange a in [a, b]
	 * @param higherRange b in [a , b]
	 * @param gridCount High value means more precision, less means
	 * more generalization.
	 */
	DimensionInfo(D lowerRange, D higherRange, AI::UINT gridCount);

	/**
	 * @return range/gridCount. Divide this with number of tilings
	 * when used for acquiring feature vector to get the real increment.
	 */
	D
	GetOffsets() const;

	/**
	 * @return usually gridCount + 1.
	 */
	AI::UINT
	GetGridCountReal() const;

	/**
	 * Changes the gridCount.
	 * @param gridCountIdeal new gridCount value.
	 */
	void
	SetGridCountIdeal(AI::UINT gridCountIdeal);

	/**
	 * @return gridCount.
	 */
	AI::UINT
	GetGridCountIdeal() const;

	/**
	 * @return Acquire the difference in range [a, b]. Or |b-a|.
	 */
	AI::FLOAT
	GetRangeDifference() const;

	/**
	 * @param upperBound to set b in range [a, b].
	 */
	void
	setUpperBound(D upperBound);

	/**
	 * @param lowerBound to set a in range [a, b].
	 */
	void
	setLowerBound(D lowerBound);

	/**
	 * @return b in range [a, b]/
	 */
	D
	getUpperBound();

	/**
	 * @return a in range [a, b].
	 */
	D
	getLowerBound();

	/**
	 * @return the generalization amount.
	 */
	AI::FLOAT
	getGeneralizationScale() const;

	/**
	 * @param generalization scales the generalization.
	 * Greater than 1 means exagerated, (0, 1), means
	 * reduced influence.
	 */
	void
	setGeneralizationScale(AI::FLOAT generalization);

private:
	std::pair<D, D> _range;
	D _rangeDifference;
	AI::UINT _gridCountIdeal;
	AI::UINT _gridCountReal;
	D _offsets;

	AI::FLOAT _generalizationScale;
};

template<typename D>
DimensionInfo<D>::DimensionInfo(D lowerRange, D higherRange,
		AI::UINT gridCount) {
	_range = std::pair<D, D>(lowerRange, higherRange);
	_rangeDifference = abs(_range.first - _range.second);
	_gridCountIdeal = gridCount;
	_gridCountReal = _gridCountIdeal + 1;
	_offsets = (_rangeDifference / _gridCountIdeal);
	_generalizationScale = 1.0F;
}

template<typename D>
D DimensionInfo<D>::GetOffsets() const {
	return _offsets;
}

template<typename D>
AI::UINT DimensionInfo<D>::GetGridCountReal() const {
	return _gridCountReal;
}

template<typename D>
void DimensionInfo<D>::SetGridCountIdeal(AI::UINT gridCountIdeal) {
	this->_gridCountIdeal = gridCountIdeal;
}

template<typename D>
AI::UINT DimensionInfo<D>::GetGridCountIdeal() const {
	return _gridCountIdeal;
}

template<typename D>
AI::FLOAT DimensionInfo<D>::GetRangeDifference() const {
	return _rangeDifference;
}

template<typename D>
void DimensionInfo<D>::setUpperBound(D upperBound) {
	_range.second = upperBound;
}

template<typename D>
void DimensionInfo<D>::setLowerBound(D lowerBound) {
	_range.first = lowerBound;
}

template<typename D>
D DimensionInfo<D>::getUpperBound() {
	return _range.second;
}

template<typename D>
D DimensionInfo<D>::getLowerBound() {
	return _range.first;
}

template<typename D>
AI::FLOAT DimensionInfo<D>::getGeneralizationScale() const {
	return _generalizationScale;
}

template<typename D>
void DimensionInfo<D>::setGeneralizationScale(AI::FLOAT generalization) {
	_generalizationScale = generalization;
}

}
}

#endif	/* DIMENSIONINFO_H */

