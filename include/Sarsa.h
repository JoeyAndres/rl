/*
 * Sarsa.h
 *
 *  Created on: May 31, 2014
 *      Author: jandres
 */

#ifndef SARSA_H_
#define SARSA_H_

#include <set>
#include <map>

#include "StateAction.h"
#include "ReinforcementLearning.h"
#include "Policy.h"

using std::set;
using std::map;

namespace AI {
namespace Algorithm {
namespace RL {

/*! \class Sarsa
 *  \brief Basic on-policy reinforcement learning algorithm.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 *
 *  The same policy is used for both learning and taking action given state.
 */
template<class S, class A>
class Sarsa : public ReinforcementLearning<S, A> {
 public:
  /**
   * @param stepSize range \f$[0.0, 1.0]\f$. High step size means faster learning, but
   * less precise convergence.
   * @param discountRate range \f$[0.0, 1.0]\f$. High discount rate means more
   * consideration of future events.
   * @param policy online policy, that is policy used for action selection.
   */
  Sarsa(AI::FLOAT stepSize, AI::FLOAT discountRate,
        Policy::Policy<S, A>& policy);

 public:
  // Inherited.

  virtual void update(const StateAction<S, A>& currentStateAction,
                      const S& nextState, const AI::FLOAT reward,
                      const set<A>& actionSet);
};

template<class S, class A>
Sarsa<S, A>::Sarsa(AI::FLOAT stepSize, AI::FLOAT discountRate,
                   Policy::Policy<S, A>& policy)
    : ReinforcementLearning<S, A>(stepSize, discountRate, policy) {
  this->setLearningPolicy(policy);
}

// TODO: Make setLearningPolicy and setPolicy the same.
template<class S, class A>
void Sarsa<S, A>::update(const StateAction<S, A>& currentStateAction,
                         const S& nextState, const AI::FLOAT reward,
                         const set<A>& actionSet) {
  ReinforcementLearning<S, A>::update(currentStateAction, nextState, reward,
                                      actionSet);
  A nextAction = this->getAction(nextState, actionSet);
  this->backUpStateActionPair(currentStateAction, reward,
                              StateAction<S, A>(nextState, nextAction));
}

} /* Sarsa */
} /* Algorithm */
} /* namespace AI */

#endif /* SARSA_H_ */
