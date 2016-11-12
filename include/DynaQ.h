/*
 * File:   DynaQ.h
 * Author: jandres
 *
 * Created on June 2, 2014, 11:09 PM
 */

#ifndef DYNAQ_H
#define	DYNAQ_H

#include <cstdint>
#include <set>
#include <map>

#include "StateAction.h"
#include "StateActionTransition.h"
#include "ReinforcementLearning.h"
#include "DynaQRLMP.h"

using namespace std;

namespace AI {
namespace Algorithm {
namespace RL {

/*! \class DynaQ
 *  \brief DynaQ algorithm implementation.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 *
 *  DynaQ algorithm is a QLearning algorithm that employs a <i>model</i>
 *  to "model" the environment. Thus, in every update, the algorithm can
 *  do \f$n\f$ simulations, enabling faster convergence to "optimal" policy.
 */
template<class S, class A>
class DynaQ : public DynaQRLMP<S, A> {
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
   */
  DynaQ(AI::FLOAT stepSize, AI::FLOAT discountRate,
        Policy::Policy<S, A>& policy, AI::UINT simulationIterationCount,
        AI::FLOAT stateTransitionGreediness, AI::FLOAT stateTransitionStepSize);

  virtual void update(const StateAction<S, A>& currentStateAction,
                      const S& nextState,
                      const FLOAT reward,
                      const set<A>& actionSet) override;
};

template<class S, class A>
DynaQ<S, A>::DynaQ(AI::FLOAT stepSize, AI::FLOAT discountRate,
                   Policy::Policy<S, A>& policy,
                   AI::UINT simulationIterationCount,
                   AI::FLOAT stateTransitionGreediness,
                   AI::FLOAT stateTransitionStepSize)
  : DynaQRLMP<S, A>(stepSize, discountRate, policy, simulationIterationCount,
                    stateTransitionGreediness, stateTransitionStepSize) {
}

template<class S, class A>
void AI::Algorithm::RL::DynaQ<S, A>::update(
  const StateAction<S, A>& currentStateAction,
  const S& nextState,
  const FLOAT reward,
  const set<A>& actionSet) {
  A nextAction = this->getLearningAction(nextState, actionSet);
  DynaQRLMP<S, A>::updateStateAction(
    currentStateAction,
    StateAction<S, A>(nextState, nextAction),
    reward);
  this->backUpStateActionPair(currentStateAction, reward,
                              StateAction<S, A>(nextState, nextAction));

  // Update model.
  this->_updateModel(currentStateAction, nextState, reward);

  // Simulation.
  this->_simulate(actionSet);
}

} // namespace RL
} /* namespace Algorithm */
} /* namespace AI */

#endif	/* DYNAQ_H */

