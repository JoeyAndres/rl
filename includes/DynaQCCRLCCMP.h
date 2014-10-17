/*
 * DynaQCCRLCCMP.h
 *
 *  Created on: Jun 14, 2014
 *      Author: jandres
 */

#ifndef DYNAQCCRLCCMP_H_
#define DYNAQCCRLCCMP_H_

#include "DynaQCCBase.h"

namespace AI {
namespace Algorithm {

/*! \class DynaQCCRLCCMP
 *  \brief Abstract/Base class for DynaQCC algorithm.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 *
 * Merge point for DynaQCC and Reinforcement Learning.
 */
template<class S, class A>
class DynaQCCRLCCMP : public DynaQCCBase<S, A>, public ReinforcementLearning<S,
    A> {
  using DynaQCCBase<S, A>::argMax;
  using DynaQCCBase<S, A>::backUpStateActionPair;
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
  DynaQCCRLCCMP(AI::FLOAT stepSize, AI::FLOAT discountRate,
                Policy::Policy<S, A>& policy, AI::UINT simulationIterationCount,
                AI::FLOAT stateTransitionGreediness,
                AI::FLOAT stateTransitionStepSize);

public:
  // Inheritance.

  virtual void backUpStateActionPair(
      const StateAction<S, A>& currentStateAction, const FLOAT reward,
      const StateAction<S, A>& nextStateActionPair);
  virtual A argMax(const S& state, const set<A>& actionSet) const;
};

} /* namespace Algorithm */
} /* namespace AI */

template<class S, class A>
inline AI::Algorithm::DynaQCCRLCCMP<S, A>::DynaQCCRLCCMP(
    AI::FLOAT stepSize, AI::FLOAT discountRate, Policy::Policy<S, A>& policy,
    AI::UINT simulationIterationCount, AI::FLOAT stateTransitionGreediness,
    AI::FLOAT stateTransitionStepSize)
    : ReinforcementLearning<S, A>(stepSize, discountRate, policy),
      DynaQCCBase<S, A>(simulationIterationCount, stateTransitionGreediness,
                        stateTransitionStepSize) {
}

template<class S, class A>
inline void AI::Algorithm::DynaQCCRLCCMP<S, A>::backUpStateActionPair(
    const StateAction<S, A>& currentStateAction, const FLOAT reward,
    const StateAction<S, A>& nextStateActionPair) {
  ReinforcementLearning<S, A>::backUpStateActionPair(currentStateAction, reward,
                                                     nextStateActionPair);
}

template<class S, class A>
inline A AI::Algorithm::DynaQCCRLCCMP<S, A>::argMax(
    const S& state, const set<A>& actionSet) const {
  return ReinforcementLearning<S, A>::argMax(state, actionSet);
}

#endif /* DYNAQCCRLCCMP_H_ */
