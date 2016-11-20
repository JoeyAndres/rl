/**
 * Sarsa.h
 *
 *  Created on: May 31, 2014
 *      Author: jandres
 */

#ifndef SARSA_H_
#define SARSA_H_

#include <set>
#include <map>

#include "../agent/StateAction.h"
#include "ReinforcementLearning.h"
#include "../policy/Policy.h"

using std::set;
using std::map;

namespace rl {
namespace algorithm {

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
  using SA = StateAction<S, A>;

  /**
   * @param stepSize range \f$[0.0, 1.0]\f$. High step size means faster learning, but
   * less precise convergence.
   * @param discountRate range \f$[0.0, 1.0]\f$. High discount rate means more
   * consideration of future events.
   * @param policy online policy, that is policy used for action selection.
   */
  Sarsa(rl::FLOAT stepSize, rl::FLOAT discountRate,
        policy::Policy<S, A>& policy);

 public:
  // Inherited.

  virtual void update(const SA& currentStateAction,
                      const spState<S>& nextState,
                      const rl::FLOAT reward,
                      const spActionSet<A>& actionSet);
};

template<class S, class A>
Sarsa<S, A>::Sarsa(rl::FLOAT stepSize,
                   rl::FLOAT discountRate,
                   policy::Policy<S, A>& policy)
    : ReinforcementLearning<S, A>(stepSize, discountRate, policy) {
  this->setLearningPolicy(policy);
}

// TODO: Make setLearningPolicy and setPolicy the same.
template<class S, class A>
void Sarsa<S, A>::update(const StateAction<S, A>& currentStateAction,
                         const spState<S>& nextState, const rl::FLOAT reward,
                         const spActionSet<A>& actionSet) {
  spAction<A> nextAction = this->getAction(nextState, actionSet);
  ReinforcementLearning<S, A>::updateStateAction(currentStateAction, SA(nextState, nextAction), reward);
  this->backUpStateActionPair(currentStateAction, reward, SA(nextState, nextAction));
}

} /* algorithm */
} /* namespace rl */

#endif /* SARSA_H_ */
