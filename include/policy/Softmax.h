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
#include <random>
#include <cassert>
#include <memory>

#include "../declares.h"
#include "../agent/StateAction.h"
#include "Policy.h"

namespace rl {
namespace policy {
/*! \class Softmax
 *  \brief Greedy action is given highest selection probability, but all others
 *         are ranked and weighted according to their value estimates.
 *
 * Greedy action is given highest selection probability, but all others
 * are ranked and weighted according to their value estimates. In contrast with
 * EpsilonGreedy algorithm where non-greedy actions have equal chance of being
 * chosen, non-greedy actions in Softmax are chosen depending on their value
 * estimates. The higher the value estimates, the more likely to be chosen.
 *
 * In essence, Softmax chooses action <i>a</i> with probability,
 *
 * \f$\dfrac{e^{\frac{Q_t(a)}{\tau}}}{\sum_{i=1}^n e^{\frac{Q_t(a)}{\tau}}}\f$
 *
 * where \f$\tau\f$ is the temperature. High temperature cause the actions to be
 * all (nearly) equiprobable. Low temperatures cause a greater difference in
 * selection probability that differ in their action estimates.
 *
 * This policy algorithm is adapted from Sutton and Barto rl book 2nd edition
 * pg 31.
 *
 * \tparam S State data type.
 * \tparam A Action data type.
 */
template<class S, class A>
class Softmax : public Policy<S, A> {
 public:
  explicit Softmax(rl::FLOAT temperature);

  spAction<A> getAction(const spActionValueMap<A>& actionValues,
                        const spActionSet<A>& actionSet) override;
  spAction<A> getAction(const spActionValueMap<A>& actionValues,
                        const spActionSet<A>& actionSet,
                        const spAction<A>& maxAction) override;
 private:
  std::random_device _randomDevice;
  std::uniform_real_distribution<rl::FLOAT> _distribution;
  rl::FLOAT _temperature;  //!< High temperature cause the actions to be all
                           //!< (nearly) equiprobable. Low temperatures cause a
                           //!< a greater difference in selection probability
                           //!< that differ in their action estimates.
};

/*! \typedef spSoftmax
 *
 *  Softmax wrapped in smart pointer.
 */
template<class S, class A>
using spSoftmax = shared_ptr<Softmax<S, A>>;

template<class S, class A>
rl::policy::Softmax<S, A>::Softmax(rl::FLOAT temperature)
    : _distribution(0.0F, 1.0F),
      _temperature(temperature) {
}

template<class S, class A>
spAction<A> rl::policy::Softmax<S, A>::getAction(
    const spActionValueMap<A>& actionValues, const spActionSet<A>& actionSet) {
  // Acquire E(i=1...n) e^(Q(i)/temp)
  rl::FLOAT sum = 0.0F;
  for (const spAction<A>& action : actionSet) {
    sum += exp(actionValues.at(action) / _temperature);
  }

  // Acquire probability for each action.
  spActionValueMap<A> actionProbabilityMap;
  for (const spAction<A>& action : actionSet) {
    rl::FLOAT probability = exp(actionValues.at(action) / _temperature) / sum;
    actionProbabilityMap[action] = probability;
  }

  // Choose action based on probability.
  rl::FLOAT randomNumberWeightedSelection = _distribution(_randomDevice);

  // Get the one that matches the random value.
  auto iter = actionProbabilityMap.begin();
  for (; iter != actionProbabilityMap.end(); iter++) {
    rl::FLOAT currentProbability = iter->second;

    // If current frequency is greater than highest frequency and at the
    // time lower than the current random number then
    // Error = randomNumber-highestFreq is of the lowest, therefore,
    // a candidate.
    if (currentProbability > randomNumberWeightedSelection) {
      return iter->first;
    }

    randomNumberWeightedSelection -= currentProbability;
  }

  assert(false);
}

template<class S, class A>
spAction<A> rl::policy::Softmax<S, A>::getAction(
  const spActionValueMap<A>& actionValues,
  const spActionSet<A>& actionSet, const spAction<A>& maxAction) {
  return getAction(actionValues, actionSet);
}

}  // namespace policy
}  // namespace rl
