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

#include <algorithm>
#include <vector>
#include <array>

#include "../../declares.h"
#include "../../coding/TileCode.h"
#include "GradientDescentTileCodeAbstract.h"

using std::vector;
using std::array;

using rl::utility::concatArray;
using rl::coding::spTileCode;

namespace rl {
namespace algorithm {

/*! \class GradientDescentTileCodeET
 *  \brief Gradient Descent eligibility traces.
 *  \tparam D Number of dimension.
 *  \tparam STATE_DIM Number of dimension in State.
 *                    This also implies ACTION_DIM = D - STATE_DIM.
 */
template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
class GradientDescentTileCodeET :
  public GradientDescentTileCodeAbstract<D, NUM_TILINGS, STATE_DIM> {
 public:
  /**
   * @param tileCode Type of tile coding.
   * @param stepSize Step size for gradient descent.
   * @param discountRate discount rate for gradient descent.
   * @param lambda How influential is current state-action to their state-action.
   */
  GradientDescentTileCodeET(
    const spTileCode<D, NUM_TILINGS>& tileCode,
    rl::FLOAT stepSize,
    rl::FLOAT discountRate,
    rl::FLOAT lambda);

  /**
   * Increase the eligibility traces of a given feature vector.
   * Note: This is loads faster than replace elibility traces.
   * @param fv feature vector.
   */
  void incrementEligibilityTraces(const FEATURE_VECTOR& fv);

  /**
   * Replace the eligibility traces for each feature vector by 1.0F.
   * @param fv feature vector.
   */
  void replaceEligibilityTraces(const FEATURE_VECTOR& fv);

  /**
   * Decrease each eligibility traces by eligibility traces and discount rate $(\lambda)$
   */
  void decreaseEligibilityTraces();

  /**
   * Make all eligibility trace to 0.0F.
   */
  void resetEligibilityTraces();

  /**
   * @param currentStateVector array of current states.
   * @param actionVector action taken to get to nextStateVector.
   * @param nextStateVector array of next states.
   * @param reward reward for taking nextAction.
   */
  void updateWeights(
    const typename GradientDescentAbstract<
      D,
      STATE_DIM>::spStateParam& currentStateVector,
    const typename GradientDescentAbstract<
      D,
      STATE_DIM>::spActionParam& currentActionVector,
    const typename GradientDescentAbstract<
      D,
      STATE_DIM>::spStateParam& nextStateVector,
    const FLOAT nextActionValue,
    const FLOAT reward) override;

  /**
   * Update weights with tderror.
   * @param tdError
   */
  virtual void backUpWeights(FLOAT tdError);

 protected:
  std::vector<rl::FLOAT> _e;  //!< Vector of eligibility traces.
};

template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
GradientDescentTileCodeET<D, NUM_TILINGS, STATE_DIM>::GradientDescentTileCodeET(
  const spTileCode<D, NUM_TILINGS>& tileCode,
  rl::FLOAT stepSize,
  rl::FLOAT discountRate,
  rl::FLOAT lambda) :
  GradientDescentTileCodeAbstract<
    D, NUM_TILINGS, STATE_DIM>::GradientDescentTileCodeAbstract(
    tileCode, stepSize, discountRate, lambda) {
  _e = floatVector(this->_courseCode->getSize(), 0);
}

template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
void GradientDescentTileCodeET<
  D, NUM_TILINGS, STATE_DIM>::incrementEligibilityTraces(
  const FEATURE_VECTOR& fv) {
  for (rl::INT f : fv) {
    ++(this->_e)[f];
  }
}

template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
void GradientDescentTileCodeET<
  D, NUM_TILINGS, STATE_DIM>::replaceEligibilityTraces(
  const FEATURE_VECTOR& fv) {
  for (rl::INT f : fv) {
    this->_e[f] = 1;
  }
}

template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
void
GradientDescentTileCodeET<
  D, NUM_TILINGS, STATE_DIM>::decreaseEligibilityTraces() {
  size_t n = this->getSize();
  for (size_t i = 0; i < n; i++) {
    this->_e[i] *= this->_discountRateTimesLambda;
  }
}

template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
void
GradientDescentTileCodeET<
  D, NUM_TILINGS, STATE_DIM>::backUpWeights(FLOAT tdError) {
  rl::FLOAT multiplier = (this->_stepSize / NUM_TILINGS) * tdError;
  size_t n = this->getSize();
  for (size_t i = 0; i < n-1; i++) {
    this->_tileCode->at(i) += multiplier*_e[i];
  }
}

template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
void GradientDescentTileCodeET<
  D, NUM_TILINGS, STATE_DIM>::updateWeights(
  const typename GradientDescentAbstract<
    D,
    STATE_DIM>::spStateParam& currentStateVector,
  const typename GradientDescentAbstract<
    D,
    STATE_DIM>::spActionParam& currentActionVector,
  const typename GradientDescentAbstract<
    D,
    STATE_DIM>::spStateParam& nextStateVector,
  const FLOAT nextActionValue,
  const FLOAT reward) {
  auto currentParams = concatArray(*currentStateVector, *currentActionVector);

  FEATURE_VECTOR currentStateFv =
    std::move(this->getFeatureVector(currentParams));
  incrementEligibilityTraces(currentStateFv);

  FLOAT tdError = reward + this->_discountRate * nextActionValue
    - this->getValueFromFeatureVector(currentStateFv);

  backUpWeights(tdError);
  // Decrease traces.
  decreaseEligibilityTraces();
}

template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
void GradientDescentTileCodeET<
  D, NUM_TILINGS, STATE_DIM>::resetEligibilityTraces() {
  std::fill(&this->_e[0], &this->_e[0] + this->getSize(), 0);
}

}  // namespace algorithm
}  // namespace rl
