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
	template<class S, class A>
	class DynaQCC: public DynaQCCRLCCMP<S, A> {
	public:
	  DynaQCC(AI::FLOAT stepSize, AI::FLOAT discountRate, Policy<S, A>& policy,
		  AI::UINT simulationIterationCount, AI::FLOAT stateTransitionGreediness,
		  AI::FLOAT stateTransitionStepSize);

	  virtual void update(const StateAction<S, A>& currentStateAction,
		  const S& nextState, const FLOAT reward, const set<A>& actionSet);
	};

  } /* namespace Algorithm */
} /* namespace AI */

template<class S, class A>
inline AI::Algorithm::DynaQCC<S, A>::DynaQCC(AI::FLOAT stepSize,
	AI::FLOAT discountRate, Policy<S, A>& policy,
	AI::UINT simulationIterationCount, AI::FLOAT stateTransitionGreediness,
	AI::FLOAT stateTransitionStepSize) :
		DynaQCCRLCCMP<S, A>(stepSize, discountRate, policy,
							   simulationIterationCount,
							   stateTransitionGreediness,
							   stateTransitionStepSize) {
}

template<class S, class A>
inline void AI::Algorithm::DynaQCC<S, A>::update(
	const StateAction<S, A>& currentStateAction, const S& nextState,
	const FLOAT reward, const set<A>& actionSet) {
  DynaQCCRLCCMP<S, A>::update(currentStateAction, nextState, reward,
										 actionSet);
  A nextAction = this->getLearningAction(nextState, actionSet);
  this->backUpStateActionPair(currentStateAction, reward,
							  StateAction<S, A>(nextState, nextAction));

// Update model.
  this->_updateModel(currentStateAction, nextState, reward);

// Simulation.
  this->_simulate(actionSet);
}

#endif /* DYNAQCC_H_ */
