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

#include <random>
#include <iostream>
#include <memory>

#include "../declares.h"
#include "../agent/StateAction.h"
#include "Policy.h"

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
  explicit EpsilonGreedy(FLOAT greediness);
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
  spAction<A> argMax(
    const spActionValueMap<A>& actionValues,
    const spActionSet<A>& actionSet) const;

  spAction<A> getAction(
    const spActionValueMap<A>& actionValues,
    const spActionSet<A>& actionSet) override;

  spAction<A> getAction(
    const spActionValueMap<A>& actionValues,
    const spActionSet<A>& actionSet,
    const spAction<A>& maxAction) override;

  /**
   * @param greediness
   */
  void setGreediness(rl::FLOAT greediness);

  /**
   * @return current greediness.
   */
  rl::FLOAT getGreediness() const;

 protected:
  std::random_device _randomDevice;
  std::uniform_real_distribution<rl::FLOAT> _distribution;
  rl::FLOAT _greediness;  //!< Probability of selecting a greedy action.
};

typedef EpsilonGreedy<rl::floatVector, rl::floatVector> EpsilonGreedySL;

/*! \typedef spEpsilonGreedy
 *
 *  EpsilonGreedy wrapped in smart pointer.
 */
template<class S, class A>
using spEpsilonGreedy = shared_ptr<EpsilonGreedy<S, A>>;

template<class S, class A>
EpsilonGreedy<S, A>::EpsilonGreedy(rl::FLOAT greediness)
    : _greediness(greediness),
      _distribution(0.0F, 1.0F) {
}

template<class S, class A>
EpsilonGreedy<S, A>::~EpsilonGreedy() {
}

template<class S, class A>
spAction<A> EpsilonGreedy<S, A>::getAction(
    const spActionValueMap<A>& actionValues,
    const spActionSet<A>& actionSet) {
  if (_greediness == 1.0F) {
    return argMax(actionValues, actionSet);
  }
  const rl::FLOAT& r = _distribution(_randomDevice);
  if (r > _greediness) {
    std::uniform_int_distribution<rl::INT> indexDistribution(
      0, actionSet.size());
    typename spActionSet<A>::const_iterator it(actionSet.begin());
    advance(it, indexDistribution(_randomDevice));
    return (*it);
  } else {
    return argMax(actionValues, actionSet);
  }
}

template<class S, class A>
spAction<A> EpsilonGreedy<S, A>::getAction(
  const spActionValueMap<A>& actionValues,
  const spActionSet<A>& actionSet,
  const spAction<A>& maxAction) {
  if (_greediness == 1.0F) {
    return maxAction;
  }
  const rl::FLOAT& r = _distribution(_randomDevice);
  if (r > _greediness) {
    std::uniform_int_distribution<rl::INT> indexDistribution(
      0, actionSet.size());
    typename spActionSet<A>::const_iterator it(actionSet.begin());
    advance(it, indexDistribution(_randomDevice));
    return (*it);
  } else {
    return maxAction;
  }
}

template<class S, class A>
spAction<A> EpsilonGreedy<S, A>::argMax(
  const spActionValueMap<A>& actionValues,
  const spActionSet<A>& actionSet) const {
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
void EpsilonGreedy<S, A>::setGreediness(
    rl::FLOAT greediness) {
  this->_greediness = greediness;
}

template<class S, class A>
rl::FLOAT EpsilonGreedy<S, A>::getGreediness() const {
  return _greediness;
}

}  // namespace policy
}  // namespace rl

