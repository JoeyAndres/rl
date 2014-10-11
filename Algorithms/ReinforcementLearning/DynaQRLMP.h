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
template<class S, class A>
class DynaQRLMP : public ReinforcementLearning<S, A>, public DynaQBase<S, A> {
  using DynaQBase<S, A>::argMax;
  using DynaQBase<S, A>::backUpStateActionPair;
 public:
  DynaQRLMP(AI::FLOAT stepSize, AI::FLOAT discountRate, Policy<S, A>& policy,
            AI::UINT simulationIterationCount,
            AI::FLOAT stateTransitionGreediness,
            AI::FLOAT stateTransitionStepSize);

  virtual void backUpStateActionPair(
      const StateAction<S, A>& currentStateAction, const AI::FLOAT reward,
      const StateAction<S, A>& nextStateActionPair);
  virtual A argMax(const S& state, const set<A>& actionSet) const;
};

} /* namespace Algorithm */
} /* namespace AI */

template<class S, class A>
inline AI::Algorithm::DynaQRLMP<S, A>::DynaQRLMP(
    AI::FLOAT stepSize, AI::FLOAT discountRate, Policy<S, A>& policy,
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
