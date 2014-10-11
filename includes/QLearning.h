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

/**
 * QLearning
 * <p>
 * An implementation of TD(0) that employs Off-Policy TD Control. Meaning
 * different policy is used for approximating q* and action-selection.
 * </p>
 */
template<class S, class A>
class QLearning : public ReinforcementLearning<S, A> {
 public:
  QLearning(AI::FLOAT stepSize, AI::FLOAT discountRate, Policy<S, A>& policy);

  /**
   * Update the stateAction map.
   * @param currentState
   * @param currentAction
   * @param nextState
   * @param currentStateActionValue Value of currentState and currentAction.
   * @param stateAction A map of StateAction to Value.
   * @param actionSet A set of all actions.
   * @return next action to be executed.
   */
  virtual void update(const StateAction<S, A>& currentStateAction,
                      const S& nextState, const AI::FLOAT reward,
                      const set<A>& actionSet);
 private:

};

template<class S, class A>
void QLearning<S, A>::update(const StateAction<S, A>& currentStateAction,
                             const S& nextState, const AI::FLOAT reward,
                             const set<A>& actionSet) {
  ReinforcementLearning<S, A>::update(currentStateAction, nextState, reward,
                                      actionSet);
  // Note: this algorithm is in pg. 145 of Sutton and Barto 2nd edition.

  // Q(S, A) <- Q(S, A) + α[ R + γ max a Q(S' , a) − Q(S, A)]
  const A& nextAction = this->getLearningAction(nextState, actionSet);

  this->backUpStateActionPair(currentStateAction, reward,
                              StateAction<S, A>(nextState, nextAction));
}

template<class S, class A>
QLearning<S, A>::QLearning(AI::FLOAT stepSize, AI::FLOAT discountRate,
                           Policy<S, A>& policy)
    : ReinforcementLearning<S, A>(stepSize, discountRate, policy) {
}
} /* Algorithm */
} /* AI */

#endif	/* QLEARNING_H */

