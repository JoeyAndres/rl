/*
 * File:   DynaQETWatkins.h
 * Author: jandres
 *
 * Created on June 2, 2014, 11:09 PM
 */

#ifndef DYNAQETWATKINS_H
#define	DYNAQETWATKINS_H

#include <cstdint>
#include <set>
#include <map>

#include "../agent/StateAction.h"
#include "../agent/StateActionTransition.h"
#include "EligibilityTraces.h"
#include "DynaQ.h"

using namespace std;

namespace rl {
namespace algorithm {

/*! \class DynaQET
 *  \brief Employs the simulation of DynaQ and eligibility traces.
 *
 * Like DynaQ, it does \f$n\f$ simlations per update, but after than performs eligibility traces.
 *
 * @see DynaQ
 * @see EligibilityTraces
 */
template<class S, class A>
class DynaQET final: public DynaQ<S, A>, public EligibilityTraces<S, A> {
 public:
  /**
   * @param stepSize range \f$[0.0, 1.0]\f$. High step size means faster learning, but
   * less precise convergence.
   * @param discountRate range \f$[0.0, 1.0]\f$. High discount rate means more
   * consideration of future events.
   * @param policy online policy, that is policy used for action selection.
   * @param simulationIterationCount number of simulations per update/backup.
   * @param stateTransitionGreediness greediness in selecting highest value model.
   * @param stateTransitionStepSize how fast does a model update a value of a
   *                                state-action pair.
   * @param lambda huge \f$\lambda\f$ means
   *                 basically back up ranging from terminal state to initial state.
   *                 Small \f$\lambda\f$ converges to TD(0).
   */
  DynaQET(rl::FLOAT stepSize, rl::FLOAT discountRate,
          policy::Policy<S, A>& policy, rl::UINT simulationIterationCount,
          rl::FLOAT stateTransitionGreediness,
          rl::FLOAT stateTransitionStepSize, rl::FLOAT lambda);

 public:
  // Inherited.

  virtual void update(const StateAction<S, A>& currentStateAction,
                      const S& nextState,
                      const rl::FLOAT currentStateActionValue,
                      const set<A>& actionSet) override;
};

template<class S, class A>
DynaQET<S, A>::DynaQET(rl::FLOAT stepSize, rl::FLOAT discountRate,
                       policy::Policy<S, A>& policy,
                       rl::UINT simulationIterationCount,
                       rl::FLOAT stateTransitionGreediness,
                       rl::FLOAT stateTransitionStepSize, rl::FLOAT lambda)
  : DynaQ<S, A>(stepSize, discountRate, policy, simulationIterationCount,
                stateTransitionGreediness, stateTransitionStepSize),
    EligibilityTraces<S, A>(lambda) {
}

template<class S, class A>
void DynaQET<S, A>::update(const StateAction<S, A>& currentStateAction,
                           const S& nextState, const rl::FLOAT reward,
                           const set<A>& actionSet) {
  A nextAction = this->getLearningAction(nextState, actionSet);

  // For some reason I need to call the grand parent class ReinforcementLearning.
  DynaQ<S, A>::updateStateAction(
    currentStateAction,
    StateAction<S, A>(nextState, nextAction),
    reward);

  EligibilityTraces<S, A>::_eligibilityTraces.insert(
    std::pair<StateAction<S, A>, rl::FLOAT>(currentStateAction, 0.0F));

  this->_updateEligibilityTraces(currentStateAction,
                                 StateAction<S, A>(nextState, nextAction),
                                 reward, this->_stateActionPairContainer,
                                 this->_stepSize, this->_discountRate);

  // Update model.
  this->_updateModel(currentStateAction, nextState, reward);

  // Simulation.
  this->_simulate(actionSet);
}

} // namespace algorithm
} // namespace rl
#endif	/* DYNAQETWATKINS_H */

