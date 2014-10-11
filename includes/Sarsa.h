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

/**
 * Sarsa
 * <p>
 * An implementation of TD(0) that employs On-Policy TD Control. Meaning
 * the same policy is used for approximating q* and action-selection.
 * </p>
 */
template<class S, class A>
class Sarsa : public ReinforcementLearning<S, A> {
 public:
  /**
   * @param greedy determines how random is getNextState() is. A value of
   * 1.0 means getNextState returns based on current likelihood of a state
   * occuring (not random). With 0.0, it will not rely on the likelihood
   * of state and return a random nextstate.
   * @param stepSize determines how the frequency is updated. A low value
   * yields to a more accurate model of the environment but slower in learning
   * environment. A value of 1.0 yields to forgeting the frequency information
   * of all other transition states, suitable for deterministic environment.
   */
  Sarsa(AI::FLOAT stepSize, AI::FLOAT discountRate, Policy::Policy<S, A>& policy);

  /**
   * Update the stateAction map.
   * @param currentState
   * @param currentAction
   * @param nextState
   * @param reward reward of the current state action value.
   * @param actionSet A set of all actions.
   * @return next action to be executed.
   */
  virtual void update(const StateAction<S, A>& currentStateAction,
                      const S& nextState, const AI::FLOAT reward,
                      const set<A>& actionSet);
};

template<class S, class A>
void Sarsa<S, A>::update(const StateAction<S, A>& currentStateAction,
                         const S& nextState, const AI::FLOAT reward,
                         const set<A>& actionSet) {
  ReinforcementLearning<S, A>::update(currentStateAction, nextState, reward,
                                      actionSet);
  const A& nextAction = this->getAction(nextState, actionSet);
  this->backUpStateActionPair(currentStateAction, reward,
                              StateAction<S, A>(nextState, nextAction));
}

template<class S, class A>
Sarsa<S, A>::Sarsa(AI::FLOAT stepSize, AI::FLOAT discountRate,
                   Policy::Policy<S, A>& policy)
    : ReinforcementLearning<S, A>(stepSize, discountRate, policy) {
  this->setLearningPolicy(policy);
}
}
} /* namespace AI */

#endif /* SARSA_H_ */
