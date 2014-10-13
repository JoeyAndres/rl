/*
 * DynaQCC.h
 *
 *  Created on: Jun 14, 2014
 *      Author: jandres
 */

#ifndef DYNAQCC_H_
#define DYNAQCC_H_

#include "DynaQCCRLCCMP.h"

namespace AI {
namespace Algorithm {

/*! \class DynaQCC
 *  \brief DynaQ that performs simulation concurrently.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 *
 *  DynaQCC must only be used when state space is large to take advantage of multi-threading.
 *  If state space is in order of thousands or more, ReinforcementLearningGD might should
 *  be used.
 */
template<class S, class A>
class DynaQCC : public DynaQCCRLCCMP<S, A> {
 public:

  /**
   * @param stepSize range \f$[0.0, 1.0]\f$j. High step size means faster learning, but
   *        less precise convergence.
   * @param discountRate range \f$[0.0, 1.0]\f$. High discount rate means more
   *        consideration of future events.
   * @param policy online policy, that is policy used for action selection.
   * @param simulationIterationCount number of simulations per update/backup.
   * @param stateTransitionGreediness greediness in selecting highest value model.
   * @param stateTransitionStepSize how fast does a model update a value of a
   *        state-action pair.
   */
  DynaQCC(AI::FLOAT stepSize, AI::FLOAT discountRate, Policy::Policy<S, A>& policy,
          AI::UINT simulationIterationCount,
          AI::FLOAT stateTransitionGreediness,
          AI::FLOAT stateTransitionStepSize);

 public:
  // Inherited.

  virtual void update(const StateAction<S, A>& currentStateAction,
                      const S& nextState, const FLOAT reward,
                      const set<A>& actionSet);
};

} /* namespace Algorithm */
} /* namespace AI */

template<class S, class A>
inline AI::Algorithm::DynaQCC<S, A>::DynaQCC(
    AI::FLOAT stepSize, AI::FLOAT discountRate, Policy::Policy<S, A>& policy,
    AI::UINT simulationIterationCount, AI::FLOAT stateTransitionGreediness,
    AI::FLOAT stateTransitionStepSize)
    : DynaQCCRLCCMP<S, A>(stepSize, discountRate, policy,
                          simulationIterationCount, stateTransitionGreediness,
                          stateTransitionStepSize) {
}

template<class S, class A>
inline void AI::Algorithm::DynaQCC<S, A>::update(
    const StateAction<S, A>& currentStateAction, const S& nextState,
    const FLOAT reward, const set<A>& actionSet) {
  DynaQCCRLCCMP<S, A>::update(currentStateAction, nextState, reward, actionSet);
  A nextAction = this->getLearningAction(nextState, actionSet);
  this->backUpStateActionPair(currentStateAction, reward,
                              StateAction<S, A>(nextState, nextAction));

// Update model.
  this->_updateModel(currentStateAction, nextState, reward);

// Simulation.
  this->_simulate(actionSet);
}

#endif /* DYNAQCC_H_ */
