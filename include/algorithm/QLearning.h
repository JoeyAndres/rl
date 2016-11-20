/* 
 * File:   QLearning.h
 * Author: jandres
 *
 * Created on June 3, 2014, 3:13 AM
 */

#ifndef QLEARNING_H
#define	QLEARNING_H

#include <set>
#include <map>

#include "../agent/StateAction.h"
#include "ReinforcementLearning.h"
#include "../policy/Policy.h"

using std::set;
using std::map;

namespace rl {
namespace algorithm {

/*! \class QLearning
 *  \brief Basic off-policy reinforcement learning algorithm.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 *
 *  Different policy is used for learning and action selection.
 *  Note that default offline/learning policy is EpsilonGreedy
 */
template<class S, class A>
class QLearning : public ReinforcementLearning<S, A> {
 public:
  /**
   * @param stepSize range \f$[0.0, 1.0]\f$. High step size means faster learning, but
   * less precise convergence.
   * @param discountRate range \f$[0.0, 1.0]\f$. High discount rate means more
   * consideration of future events.
   * @param policy online policy, that is policy used for action selection.
   */
  QLearning(rl::FLOAT stepSize, rl::FLOAT discountRate,
            policy::Policy<S, A>& policy);

  virtual void update(const StateAction<S, A>& currentStateAction,
                      const spState<S>& nextState, const rl::FLOAT reward,
                      const spActionSet<A>& actionSet) override;
};

template<class S, class A>
QLearning<S, A>::QLearning(rl::FLOAT stepSize, rl::FLOAT discountRate,
                           policy::Policy<S, A>& policy)
    : ReinforcementLearning<S, A>(stepSize, discountRate, policy) {
}

template<class S, class A>
void QLearning<S, A>::update(const StateAction<S, A>& currentStateAction,
                             const spState<S>& nextState,
                             const rl::FLOAT reward,
                             const spActionSet<A>& actionSet) {
  // Note: this algorithm is in pg. 145 of Sutton Barto 2nd edition.
  // Q(S, A) <- Q(S, A) + α[ R + γ max a Q(S' , a) − Q(S, A)]
  spAction<A> nextAction = this->getLearningAction(nextState, actionSet);

  ReinforcementLearning<S, A>::updateStateAction(currentStateAction,
                                      StateAction<S, A>(nextState, nextAction),
                                      reward);

  this->backUpStateActionPair(currentStateAction, reward,
                              StateAction<S, A>(nextState, nextAction));
}

} /* algorithm */
} /* rl */

#endif	/* QLEARNING_H */

