/*
 * File:   ReinforcementLearningET.h
 * Author: jandres
 *
 * Created on June 7, 2014, 6:07 AM
 */

#ifndef REINFORCEMENTLEARNINGET_H
#define	REINFORCEMENTLEARNINGET_H

#include "GlobalHeader.h"

#include <map>

#include "StateAction.h"
#include "StateActionPairContainer.h"

using namespace std;

namespace AI {
  namespace Algorithm {

	/**
	 * EligibilityTraces
	 * As opposed to ordinary Temporal Difference or whats called in the
	 * literature as TD(0), eligibility traces TD(lambda) bridges the
	 * gap between TD(0) and Monte Carlo methods. A huge lambda means
	 * basically back up ranging from terminal state to initial state.
	 * Small lambda converges to TD(0).
	 *
	 * Note that there is a performance penalty as result of having
	 * to iterate all of state space.
	 *
	 * TODO: Make another parent class for all other eligibility trace algorithm that contains
	 * a merge of RL and Eligibility traces. This way, we can syc some shit.
	 *
	 * TODO: Connect the reset() to resetEligibilityTraces() function that have yet to be made.
	 */
	template<class S, class A>
	class EligibilityTraces {
	public:
	  /**
	   * @param lambda A huge lambda means basically back up ranging from
	   * terminal state to initial state. Small lambda converges to TD(0).
	   */
	  EligibilityTraces(AI::FLOAT lambda);

	  /**
	   * @param lambda
	   */
	  void setLambda(AI::FLOAT lambda);

	  /**
	   * @return current lambda.
	   */
	  AI::FLOAT getLambda() const;

	protected:
	  virtual void _updateEligibilityTraces(
		  const StateAction<S, A>& currentStateAction,
		  const StateAction<S, A>& nextStateAction, AI::FLOAT reward,
		  StateActionPairContainer<S, A>& stateActionPairValueMap,
		  AI::FLOAT stepSize, AI::FLOAT discountRate);

	protected:
	  AI::FLOAT _lambda;
	  map<StateAction<S, A>, AI::FLOAT> _eligibilityTraces;
	};

	template<class S, class A>
	EligibilityTraces<S, A>::EligibilityTraces(AI::FLOAT lambda) :
			_lambda(lambda) {
	}

	template<class S, class A>
	void EligibilityTraces<S, A>::setLambda(AI::FLOAT lambda) {
	  this->_lambda = lambda;
	}

	template<class S, class A>
	AI::FLOAT EligibilityTraces<S, A>::getLambda() const {
	  return _lambda;
	}
	// todo: encapsulate eligibilitytraces map to prepare for concurrency.
	template<class S, class A>
	void EligibilityTraces<S, A>::_updateEligibilityTraces(
		const StateAction<S, A>& currentStateAction,
		const StateAction<S, A>& nextStateAction, AI::FLOAT reward,
		StateActionPairContainer<S, A>& stateActionPairValue,
		AI::FLOAT stepSize, AI::FLOAT discountRate) {

	  AI::FLOAT tdError = reward
		  + discountRate * (reward
			  + discountRate * stateActionPairValue[nextStateAction]
							- stateActionPairValue[currentStateAction]);
	  _eligibilityTraces[currentStateAction] =
		  _eligibilityTraces[currentStateAction] + 1;

	  for (auto iter = stateActionPairValue.begin();
		  iter != stateActionPairValue.end(); iter++) {
		const S& state = iter->first.getState();
		const A& action = iter->first.getAction();
		AI::FLOAT value = iter->second;

		stateActionPairValue.setStateActionValue(
			StateAction<S, A>(state, action),
			value + stepSize
				* tdError
				* this->_eligibilityTraces[StateAction<S, A>(state, action)]);

		_eligibilityTraces[StateAction<S, A>(state, action)] = discountRate
			* this->_lambda
			* this->_eligibilityTraces[StateAction<S, A>(state, action)];
	  }
	}
  }
}

#endif	/* REINFORCEMENTLEARNINGET_H */

