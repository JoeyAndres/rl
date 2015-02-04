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

#include "StateAction.h"
#include "ReinforcementLearning.h"
#include "Policy.h"

using std::set;
using std::map;

namespace AI {
namespace Algorithm {
namespace RL {

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
  QLearning(AI::FLOAT stepSize, AI::FLOAT discountRate,
            Policy::Policy<S, A>& policy);

  virtual void update(const StateAction<S, A>& currentStateAction,
                      const S& nextState, const AI::FLOAT reward,
                      const set<A>& actionSet) override;
};

template<class S, class A>
QLearning<S, A>::QLearning(AI::FLOAT stepSize, AI::FLOAT discountRate,
                           Policy::Policy<S, A>& policy)
    : ReinforcementLearning<S, A>(stepSize, discountRate, policy) {
}

template<class S, class A>
void QLearning<S, A>::update(const StateAction<S, A>& currentStateAction,
                             const S& nextState, const AI::FLOAT reward,
                             const set<A>& actionSet) {
  ReinforcementLearning<S, A>::update(currentStateAction, nextState, reward,
                                      actionSet);

  // Note: this algorithm is in pg. 145 of Sutton Barto 2nd edition.
  // Q(S, A) <- Q(S, A) + α[ R + γ max a Q(S' , a) − Q(S, A)]
  A nextAction = this->getLearningAction(nextState, actionSet);

  this->backUpStateActionPair(currentStateAction, reward,
                              StateAction<S, A>(nextState, nextAction));
}

} /* QLearning */
} /* Algorithm */
} /* AI */

#endif	/* QLEARNING_H */

