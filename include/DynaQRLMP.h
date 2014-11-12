/*
 * DynaQRLMP.h
 *
 *  Created on: Jun 14, 2014
 *      Author: jandres
 */

#ifndef DYNAQRLMP_H_
#define DYNAQRLMP_H_

#include "DynaQBase.h"
#include "ReinforcementLearning.h"

namespace AI {
namespace Algorithm {

/*! \class DynaQRLMP
 *  \brief Abstract class that represents the merge Point for DynaQBase and
 *         Reinforcement Learning.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 *
 *  This class is still so DynaQBase aggregate Reinforcement Learning functions.
 *  Note that although <b>DynaQBase::argMax</b> and <b>DynaQBase::backUpStateActionPair</b>
 *  are used, they both aggregate ReinforcementLearning::argMax and
 *  ReinforcementLearning::backUpStateActionPair.
 */
template<class S, class A>
class DynaQRLMP : public ReinforcementLearning<S, A>, public DynaQBase<S, A> {
  using DynaQBase<S, A>::argMax;
  using DynaQBase<S, A>::backUpStateActionPair;
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
  DynaQRLMP(AI::FLOAT stepSize, AI::FLOAT discountRate,
            Policy::Policy<S, A>& policy, AI::UINT simulationIterationCount,
            AI::FLOAT stateTransitionGreediness,
            AI::FLOAT stateTransitionStepSize);

 public:
  // Inherited. Note that, although inherited, documentation have to be reintroduced due
  // to functions aggregating each other.

  /**
   * Does the main back up for all Temporal difference:
   * \f$ Q[S, A] \leftarrow Q[S, A] + \alpha\times [R + \gamma \times max_{A'}Q[S', A'] - Q[S, A] ]\f$
   * @param currentStateAction \f$(S, A)\f$, current state-action pair.
   * @param reward \f$R\f$, reward after \f$(S, A)\f$.
   * @param nextStateActionPair \f$(S', A')\f$, next state-action pair.
   */
  virtual void backUpStateActionPair(
      const StateAction<S, A>& currentStateAction, const AI::FLOAT reward,
      const StateAction<S, A>& nextStateActionPair);

  /**
   * Returns the action that will most "likely" gives the highest reward from the
   * current state.
   * @param state the state to apply the argMax to.
   * @param stateAction map of StateAction to value.
   * @param actionSet a set of possible actions.
   * @return the action that will "likely" gives the highest reward.
   */
  virtual A argMax(const S& state, const set<A>& actionSet) const;
};

} /* namespace Algorithm */
} /* namespace AI */

template<class S, class A>
inline AI::Algorithm::DynaQRLMP<S, A>::DynaQRLMP(
    AI::FLOAT stepSize, AI::FLOAT discountRate, Policy::Policy<S, A>& policy,
    AI::UINT simulationIterationCount, AI::FLOAT stateTransitionGreediness,
    AI::FLOAT stateTransitionStepSize)
    : ReinforcementLearning<S, A>(stepSize, discountRate, policy),
      DynaQBase<S, A>(simulationIterationCount, stateTransitionGreediness,
                      stateTransitionStepSize) {
}

template<class S, class A>
inline void AI::Algorithm::DynaQRLMP<S, A>::backUpStateActionPair(
    const StateAction<S, A>& currentStateAction, const AI::FLOAT reward,
    const StateAction<S, A>& nextStateActionPair) {
  ReinforcementLearning<S, A>::backUpStateActionPair(currentStateAction, reward,
                                                     nextStateActionPair);
}

template<class S, class A>
inline A AI::Algorithm::DynaQRLMP<S, A>::argMax(const S& state,
                                                const set<A>& actionSet) const {
  return ReinforcementLearning<S, A>::argMax(state, actionSet);
}

#endif /* DYNAQRLMP_H_ */
