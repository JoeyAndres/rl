/* 
 * File:   Softmax.h
 * Author: jandres
 *
 * Created on June 7, 2014, 4:43 AM
 */

#ifndef SOFTMAX_H
#define	SOFTMAX_H

#include "GlobalHeader.h"

#include <cmath>
#include <random>
#include <cassert>

#include "Policy.h"
#include "StateAction.h"

using namespace std;

namespace AI {
namespace Algorithm {
namespace Policy {
/**
 * Softmax Policy
 * <p>
 * Softmax places a probability to each action during action selection.
 * A state action pair with greater value yields to higher chance of being
 * chosen as next action. As opposed to epsilon greedy, this choses its
 * action not randomly.
 * <b>temperature</b> is the attribute that controls the greediness.
 * Lower temperature means discrepancy of probability is magnified, making
 * softmax close to greedy. High temperature means a more realistic representation
 * of probabilities.
 * </p>
 * This policy algorithm is adapted from Sutton and Barto RL book 2nd edition
 * pg 31.
 */
template<class S, class A>
class Softmax : public Policy<S, A> {
 public:
  Softmax(AI::FLOAT temperature);

  virtual const A& getAction(const map<A, AI::FLOAT>& actionValues,
                             const set<A>& actionSet);

 private:
  std::random_device _randomDevice;
  std::uniform_real_distribution<AI::FLOAT> _distribution;
  AI::FLOAT _temperature;
};

typedef Softmax<vector<AI::FLOAT>, vector<AI::FLOAT> > SoftmaxSL;
}
}
}

template<class S, class A>
AI::Algorithm::Policy::Softmax<S, A>::Softmax(AI::FLOAT temperature)
    : _distribution(0.0F, 1.0F) {
  _temperature = temperature;
}

template<class S, class A>
const A& AI::Algorithm::Policy::Softmax<S, A>::getAction(
    const map<A, AI::FLOAT>& actionValues, const set<A>& actionSet) {
  // Acquire E(i=1...n) e^(Q(i)/temp)
  AI::FLOAT sum = 0.0F;
  for (const A& action : actionSet) {
    sum += exp(actionValues.at(action) / _temperature);
  }

  // Acquire probability for each action.
  map<A, AI::FLOAT> actionProbabilityMap;
  for (const A& action : actionSet) {
    AI::FLOAT probability = exp(actionValues.at(action) / _temperature) / sum;
    actionProbabilityMap[action] = probability;
  }

  // Choose action based on probability.
  AI::FLOAT randomNumberWeightedSelection = _distribution(_randomDevice);

  // Get the one that matches the random value.
  auto iter = actionProbabilityMap.begin();
  for (; iter != actionProbabilityMap.end(); iter++) {
    AI::FLOAT currentProbability = iter->second;

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

#endif	/* SOFTMAX_H */

