/*
 * SarsaET.h
 *
 *  Created on: May 31, 2014
 *      Author: jandres
 */

#ifndef SARSAETWATKINS_H_
#define SARSAETWATKINS_H_

#include <set>
#include <map>

#include "StateAction.h"
#include "Policy.h"
#include "EligibilityTraces.h"
#include "Sarsa.h"

using std::set;
using std::map;

namespace AI {
namespace Algorithm {

/**
 * SarsaET
 * @see Sarsa
 * @see EligibilityTraces
 */
template<class S, class A>
class SarsaET final: public EligibilityTraces<S, A>, public Sarsa<S, A> {
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
  SarsaET(AI::FLOAT stepSize, AI::FLOAT discountRate, Policy<S, A>& policy,
          AI::FLOAT lambda);

  /**
   * Update the stateAction map.
   * @param currentState
   * @param currentAction
   * @param nextState
   * @param reward reward of the current state action value.
   * @param stateAction A map of StateAction to Value.
   * @param actionSet A set of all actions.
   * @return next action to be executed.
   */
  virtual void update(const StateAction<S, A>& currentStateAction,
                      const S& nextState, const AI::FLOAT reward,
                      const set<A>& actionSet);
};

template<class S, class A>
void SarsaET<S, A>::update(const StateAction<S, A>& currentStateAction,
                           const S& nextState, const AI::FLOAT reward,
                           const set<A>& actionSet) {
  ReinforcementLearning<S, A>::update(currentStateAction, nextState, reward,
                                      actionSet);
  EligibilityTraces<S, A>::_eligibilityTraces.insert(
      std::pair<StateAction<S, A>, AI::FLOAT>(currentStateAction, 0.0F));
  A nextAction = this->getAction(nextState, actionSet);

  this->_updateEligibilityTraces(currentStateAction,
                                 StateAction<S, A>(nextState, nextAction),
                                 reward, this->_stateActionPairContainer,
                                 this->_stepSize, this->_discountRate);
}

template<class S, class A>
SarsaET<S, A>::SarsaET(AI::FLOAT stepSize, AI::FLOAT discountRate,
                       Policy<S, A>& policy, AI::FLOAT lambda)
    : EligibilityTraces<S, A>(lambda),
      Sarsa<S, A>(stepSize, discountRate, policy) {
}
}
} /* namespace AI */

#endif /* SARSA_H_ */
