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

#include "../agent/StateAction.h"
#include "../policy/Policy.h"
#include "EligibilityTraces.h"
#include "Sarsa.h"

using std::set;
using std::map;

namespace rl {
namespace algorithm {

/*! \class SarsaET
 *  \brief Like Sarsa in that it uses the same policy for learning and action
 *         selection. Each iteration, it updates all other states via eligibility
 *         traces, making for faster convergence.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 */
template<class S, class A>
class SarsaET final: public EligibilityTraces<S, A>, public Sarsa<S, A> {
 public:
  /**
   * @param stepSize range \f$[0.0, 1.0]\f$. High step size means faster learning, but
   * less precise convergence.
   * @param discountRate range \f$[0.0, 1.0]\f$. High discount rate means more
   * consideration of future events.
   * @param policy online policy, that is policy used for action selection.
   * @param lambda huge \f$\lambda\f$ means
   *                 basically back up ranging from terminal state to initial state.
   *                 Small \f$\lambda\f$ converges to TD(0).
   */
  SarsaET(rl::FLOAT stepSize, rl::FLOAT discountRate,
          policy::Policy<S, A>& policy, rl::FLOAT lambda);
  
  virtual void update(const StateAction<S, A>& currentStateAction,
                      const spState<S>& nextState, const rl::FLOAT reward,
                      const spActionSet<A>& actionSet) override;
};

template<class S, class A>
void SarsaET<S, A>::update(const StateAction<S, A>& currentStateAction,
                           const spState<S>& nextState, const rl::FLOAT reward,
                           const spActionSet<A>& actionSet) {
  spAction<A> nextAction = this->getAction(nextState, actionSet);
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
SarsaET<S, A>::SarsaET(rl::FLOAT stepSize, rl::FLOAT discountRate,
                       policy::Policy<S, A>& policy, rl::FLOAT lambda)
    : EligibilityTraces<S, A>(lambda),
      Sarsa<S, A>(stepSize, discountRate, policy) {
}

} /* algorithm */
} /* rl */

#endif /* SARSA_H_ */
