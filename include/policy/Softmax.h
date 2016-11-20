/* 
 * File:   Softmax.h
 * Author: jandres
 *
 * Created on June 7, 2014, 4:43 AM
 */

#ifndef SOFTMAX_H
#define	SOFTMAX_H

#include "../declares.h"

#include <cmath>
#include <random>
#include <cassert>

#include "Policy.h"
#include "../agent/StateAction.h"

using namespace std;

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
  Softmax(rl::FLOAT temperature);

  virtual spAction<A> getAction(const spActionValueMap<A>& actionValues,
                             const spActionSet<A>& actionSet) override;
  virtual spAction<A> getAction(const spActionValueMap<A>& actionValues,
                      const spActionSet<A>& actionSet, const spAction<A>& maxAction) override;
 private:
  std::random_device _randomDevice;
  std::uniform_real_distribution<rl::FLOAT> _distribution;
  rl::FLOAT _temperature;  //!< High temperature cause the actions to be all
                           //!< (nearly) equiprobable. Low temperatures cause a
                           //!< a greater difference in selection probability
                           //!< that differ in their action estimates.
};

typedef Softmax<vector<rl::FLOAT>, vector<rl::FLOAT> > SoftmaxSL;

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
  const spActionSet<A>& actionSet, const spAction<A>& maxAction){
  return getAction(actionValues, actionSet);
}

}  // Policy
}  // rl

#endif	/* SOFTMAX_H */

