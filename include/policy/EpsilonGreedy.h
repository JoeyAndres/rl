/* 
 * File:   EpsilonGreedy.h
 * Author: jandres
 *
 * Created on June 6, 2014, 6:11 PM
 */

#ifndef EPSILONGREEDY_H
#define	EPSILONGREEDY_H

#include "../declares.h"

#include <random>
#include <iostream>

#include "Policy.h"
#include "../agent/StateAction.h"

using namespace std;

namespace rl {
namespace policy {

/*! \class EpsilonGreedy
 *  \brief Selects greedy action with probability <i>greediness</i>
 *
 *  Let \f$ 0 \leq greediness < 1 \f$, which is the probability of selecting optimal
 *  action. During the selection of non-optimal, they are selected in equiprobable
 *  manner.
 *
 *  \tparam S State data type.
 *  \tparam A Action data type.
 */
template<class S, class A>
class EpsilonGreedy : public Policy<S, A> {
 public:
  /**
   * @param greediness probability of selecting greedy action.
   */
  EpsilonGreedy(rl::FLOAT greediness);
  virtual ~EpsilonGreedy();

  /**
   * Returns the action that will "likely" gives the highest reward from the current
   * state.
   *
   * @param state the state to apply the argMax to.
   * @param stateAction map of StateAction to value.
   * @param actionSet a set of possible actions.
   * @return the action that will "likely" gives the highest reward.
   */
  A argMax(const map<A, rl::FLOAT>& actionValues, const set<A>& actionSet) const;

  virtual A getAction(const map<A, rl::FLOAT>& actionValues, const set<A>& actionSet);

  virtual A getAction(const map<A, rl::FLOAT>& actionValues, const set<A>& actionSet,
                      const A& maxAction);
  
  /**
   * @param greediness
   */
  void setGreediness(rl::FLOAT greediness);

  /**
   * @return current greediness.
   */
  rl::FLOAT getGreediness() const;
 protected:
  random_device _randomDevice;
  uniform_real_distribution<rl::FLOAT> _distribution;
  rl::FLOAT _greediness;  //!< Probability of selecting a greedy action.
};

typedef EpsilonGreedy<vector<rl::FLOAT>, vector<rl::FLOAT> > EpsilonGreedySL;

template<class S, class A>
rl::policy::EpsilonGreedy<S, A>::EpsilonGreedy(rl::FLOAT greediness)
    : _greediness(greediness),
      _distribution(0.0F, 1.0F) {
}

template<class S, class A>
rl::policy::EpsilonGreedy<S, A>::~EpsilonGreedy() {
}

template<class S, class A>
A rl::policy::EpsilonGreedy<S, A>::getAction(
    const map<A, rl::FLOAT>& actionValues, const set<A>& actionSet) {
  if(_greediness==1.0F) return argMax(actionValues, actionSet);
  const rl::FLOAT& r = _distribution(_randomDevice);
  if (r > _greediness) {
    uniform_int_distribution<rl::INT> indexDistribution(0, actionSet.size());
    typename set<A>::const_iterator it(actionSet.begin());
    advance(it, indexDistribution(_randomDevice));
    return (*it);
  } else {
    return argMax(actionValues, actionSet);
  }
}

template<class S, class A>
A rl::policy::EpsilonGreedy<S, A>::getAction(
    const map<A, rl::FLOAT>& actionValues,
    const set<A>& actionSet, const A& maxAction){
  if(_greediness == 1.0F) return maxAction;
  const rl::FLOAT& r = _distribution(_randomDevice);
  if (r > _greediness) {
    uniform_int_distribution<rl::INT> indexDistribution(0, actionSet.size());
    typename set<A>::const_iterator it(actionSet.begin());
    advance(it, indexDistribution(_randomDevice));
    return (*it);
  } else {
    return maxAction;
  }
}

template<class S, class A>
A rl::policy::EpsilonGreedy<S, A>::argMax(
    const map<A, rl::FLOAT>& actionValues, const set<A>& actionSet) const {
  auto maxActionIter = actionSet.begin();
  rl::FLOAT maxVal = actionValues.at(*maxActionIter);
  for (auto iter = actionSet.begin(); iter != actionSet.end(); ++iter) {
    if (actionValues.at(*iter) > maxVal) {
      maxActionIter = iter;
      maxVal = actionValues.at(*maxActionIter);
    }
  }

  return (*maxActionIter);
}

template<class S, class A>
void rl::policy::EpsilonGreedy<S, A>::setGreediness(
    rl::FLOAT greediness) {
  this->_greediness = greediness;
}

template<class S, class A>
rl::FLOAT rl::policy::EpsilonGreedy<S, A>::getGreediness() const {
  return _greediness;
}

}  // Policy
}  // rl

#endif	/* EPSILONGREEDY_H */

