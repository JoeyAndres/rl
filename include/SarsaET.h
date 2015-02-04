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
namespace RL {

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
  SarsaET(AI::FLOAT stepSize, AI::FLOAT discountRate,
          Policy::Policy<S, A>& policy, AI::FLOAT lambda);
  
  virtual void update(const StateAction<S, A>& currentStateAction,
                      const S& nextState, const AI::FLOAT reward,
                      const set<A>& actionSet) override;
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
                       Policy::Policy<S, A>& policy, AI::FLOAT lambda)
    : EligibilityTraces<S, A>(lambda),
      Sarsa<S, A>(stepSize, discountRate, policy) {
}

} /* SarsaET */
} /* Algorithm */
} /* AI */

#endif /* SARSA_H_ */
