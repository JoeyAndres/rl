/* 
 * File:   QLearningETWatkinsETWatkins.h
 * Author: jandres
 *
 * Created on June 7, 2014, 8:22 AM
 */

#ifndef QLEARNINGETWATKINS_H
#define	QLEARNINGETWATKINS_H

#include <set>
#include <map>

#include "../agent/StateAction.h"
#include "EligibilityTraces.h"
#include "../policy/Policy.h"
#include "QLearning.h"

using std::set;
using std::map;

namespace rl {
namespace algorithm {

/*! \class QLearningET
 *  \brief Like QLearning in that it uses different policy for learning and action
 *         selection. Each iteration, it updates all other states via eligibility
 *         traces, making for faster convergence.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 */
template<class S, class A>
class QLearningET final: public EligibilityTraces<S, A>, public QLearning<S, A> {
 public:
  QLearningET(rl::FLOAT stepSize, rl::FLOAT discountRate,
              policy::Policy<S, A>& policy, rl::FLOAT lambda);

 public:
  // Inherited.

  virtual void update(const StateAction<S, A>& currentStateAction,
                      const spState<S>& nextState,
                      const rl::FLOAT currentStateActionValue,
                      const spActionSet<A>& actionSet);
 private:

};

template<class S, class A>
void QLearningET<S, A>::update(const StateAction<S, A>& currentStateAction,
                               const spAction<S>& nextState, const rl::FLOAT reward,
                               const spActionSet<A>& actionSet) {
  spAction<A> nextAction = this->getLearningAction(nextState, actionSet);
  ReinforcementLearning<S, A>::updateStateAction(
    currentStateAction,
    StateAction<S, A>(nextState, nextAction),
    reward);
  EligibilityTraces<S, A>::_eligibilityTraces.insert(
    std::pair<StateAction<S, A>, rl::FLOAT>(currentStateAction, 0.0F));

  this->_updateEligibilityTraces(currentStateAction,
                                 StateAction<S, A>(nextState, nextAction),
                                 reward, this->_stateActionPairContainer,
                                 this->_stepSize, this->_discountRate);
}

template<class S, class A>
QLearningET<S, A>::QLearningET(rl::FLOAT stepSize, rl::FLOAT discountRate,
                               policy::Policy<S, A>& policy, rl::FLOAT lambda)
  : EligibilityTraces<S, A>(lambda),
    QLearning<S, A>(stepSize, discountRate, policy) {
}

} // namespace algorithm
} // namespace rl

#endif	/* QLEARNINGETWATKINS_H */

