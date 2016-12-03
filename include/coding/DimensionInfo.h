/**
 * rl - Reinforcement Learning
 * Copyright (C) 2016  Joey Andres<yeojserdna@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <cmath>
#include <utility>

#include "../declares.h"

using std::pair;

namespace rl {
namespace coding {

/*! \DimensionInfo
 *  \brief Encapsulate tile code dimension.
 *  \tparam D rl::FLOAT and rl:INT.
 *
 *  Encapsulate tile code dimension information.
 *
 *  TODO: Update other variables in methods.
 */
template<typename D = rl::FLOAT>
class DimensionInfo {
 public:
  /**
   * DimensionInfo consist of range [a, b] and gridCount. Higher
   * grid count means more precision, less grid count means more
   * generalization.
   * @param lowerRange a in \f$[a, b]\f$
   * @param higherRange b in \f$[a , b]\f$
   * @param gridCount High value means more precision, less means
   * more generalization.
   * @param generalizationScale scales the generalization.
   *   Greater than 1 means exaggerated, \f$[0, 1]\f$, otherwise,
   *   reduced influence.
   */
  DimensionInfo(D lowerRange, D higherRange, rl::UINT gridCount);
  DimensionInfo(D lowerRange, D higherRange, rl::UINT gridCount,
                rl::FLOAT generalizationScale);

  /**
   * @return range/gridCount. Divide this with number of tilings
   * when used for acquiring feature vector to get the real increment.
   */
  D GetOffsets() const;

  /**
   * @return usually gridCount + 1.
   */
  rl::UINT GetGridCountReal() const;

  /**
   * Changes the gridCount.
   * @param gridCountIdeal new gridCount value.
   */
  void SetGridCountIdeal(rl::UINT gridCountIdeal);

  /**
   * @return gridCount.
   */
  rl::UINT GetGridCountIdeal() const;

  /**
   * @return Acquire the difference in range \f$[a, b]\f$. Or \f$|b-a|\f$.
   */
  rl::FLOAT GetRangeDifference() const;

  /**
   * @param upperBound to set b in range \f$[a, b]\f$.
   */
  void setUpperBound(D upperBound);

  /**
   * @param lowerBound to set a in range \f$[a, b]\f$.
   */
  void setLowerBound(D lowerBound);

  /**
   * @return b in range \f$[a, b]\f$
   */
  D getUpperBound();

  /**
   * @return a in range \f$[a, b]\f$.
   */
  D getLowerBound();

  /**
   * @return the generalization amount.
   */
  rl::FLOAT getGeneralizationScale() const;

  /**
   * @param generalization scales the generalization.
   * Greater than 1 means exagerated, (0, 1), otherwise,
   * reduced influence.
   */
  void setGeneralizationScale(rl::FLOAT generalization);

 private:
  std::pair<D, D> _range;  //!< Pair of lower and upper range of the domain.
  rl::UINT _gridCountIdeal;  //!< How many equally distanced sample points do
  //!< we take from domain.
  rl::FLOAT _generalizationScale;  //!< How far do we deviate from the sample.
};

template<typename D>
DimensionInfo<D>::DimensionInfo(D lowerRange, D higherRange,
                                rl::UINT gridCount) {
  _range = std::pair<D, D>(lowerRange, higherRange);
  _gridCountIdeal = gridCount;
  _generalizationScale = 1.0F;
}

template<typename D>
DimensionInfo<D>::DimensionInfo(D lowerRange, D higherRange, rl::UINT gridCount,
                                rl::FLOAT generalizationScale) {
  _range = std::pair<D, D>(lowerRange, higherRange);
  _gridCountIdeal = gridCount;
  _generalizationScale = generalizationScale;
}

template<typename D>
D DimensionInfo<D>::GetOffsets() const {
  return (this->GetRangeDifference() / _gridCountIdeal);
}

template<typename D>
rl::UINT DimensionInfo<D>::GetGridCountReal() const {
  return _gridCountIdeal + 1;
}

template<typename D>
void DimensionInfo<D>::SetGridCountIdeal(rl::UINT gridCountIdeal) {
  this->_gridCountIdeal = gridCountIdeal;
}

template<typename D>
rl::UINT DimensionInfo<D>::GetGridCountIdeal() const {
  return _gridCountIdeal;
}

template<typename D>
rl::FLOAT DimensionInfo<D>::GetRangeDifference() const {
  return std::abs(_range.first - _range.second);
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
rl::FLOAT DimensionInfo<D>::getGeneralizationScale() const {
  return _generalizationScale;
}

template<typename D>
void DimensionInfo<D>::setGeneralizationScale(rl::FLOAT generalization) {
  _generalizationScale = generalization;
}

typedef DimensionInfo<rl::FLOAT> DimensionInfoF;  // DimensionalInfo for Floats

}  // namespace coding
}  // namespace rl

