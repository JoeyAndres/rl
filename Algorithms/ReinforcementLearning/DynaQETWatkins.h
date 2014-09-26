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

#include "StateAction.h"
#include "StateActionTransition.h"
#include "EligibilityTraces.h"
#include "DynaQ.h"

using namespace std;

namespace AI {
  namespace Algorithm {

	/**
	 * DynaQETWatkins
	 * <p>The DynaQETWatkins algorithm is a subclass of Reinforcement Algorithm.
	 * DynaQETWatkins employs simulationCount for every update thus improving
	 * the conversion rate.</p>
	 *
	 * @see StateActionTransition representing the models.
	 *
	 * @see DynaQ
	 * @see EligibilityTraces
	 */
	template<class S, class A>
	class DynaQETWatkins final: public DynaQ<S, A>, public EligibilityTraces<S,
		A> {
	public:
	  /**
	   * @param stepSize range [0.0, 1.0]. High step size means faster learning, but less precise convergence.
	   * @param discountRate range [0.0, 1.0]. High discount rate means more consideration of future events.
	   * @param simulationIterationCount How many simulation per update.
	   * @param stateTransitionGreediness High value means less likely to choose random action during simulation.
	   * @param stateTransitionStepSize High value means faster learning in models but lower values means more accurate models.
	   */
	  DynaQETWatkins(AI::FLOAT stepSize, AI::FLOAT discountRate, Policy<S, A>& policy,
		  AI::UINT simulationIterationCount, AI::FLOAT stateTransitionGreediness,
		  AI::FLOAT stateTransitionStepSize, AI::FLOAT lambda);

	  virtual void update(const StateAction<S, A>& currentStateAction,
		  const S& nextState, const AI::FLOAT currentStateActionValue,
		  const set<A>& actionSet);
	};

	template<class S, class A>
	DynaQETWatkins<S, A>::DynaQETWatkins(AI::FLOAT stepSize, AI::FLOAT discountRate,
		Policy<S, A>& policy, AI::UINT simulationIterationCount,
		AI::FLOAT stateTransitionGreediness, AI::FLOAT stateTransitionStepSize,
		AI::FLOAT lambda) :
			DynaQ<S, A>(stepSize, discountRate, policy,
						simulationIterationCount, stateTransitionGreediness,
						stateTransitionStepSize),
			EligibilityTraces<S, A>(lambda) {
	}

	template<class S, class A>
	void DynaQETWatkins<S, A>::update(
		const StateAction<S, A>& currentStateAction, const S& nextState,
		const AI::FLOAT reward, const set<A>& actionSet) {
	  ReinforcementLearning<S, A>::update(currentStateAction, nextState, reward,
										  actionSet);

	  EligibilityTraces<S, A>::_eligibilityTraces.insert(
		  std::pair<StateAction<S, A>, AI::FLOAT>(currentStateAction, 0.0F));
	  A nextAction = this->getLearningAction(nextState, actionSet);

	  this->_updateEligibilityTraces(currentStateAction,
									 StateAction<S, A>(nextState, nextAction),
									 reward, this->_stateActionPairContainer,
									 this->_stepSize, this->_discountRate);

	  // Update model.
	  this->_updateModel(currentStateAction, nextState, reward);

	  // Simulation.
	  this->_simulate(actionSet);
	}
  } /* namespace Algorithm */
} /* namespace AI */
#endif	/* DYNAQETWATKINS_H */

