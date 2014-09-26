/*
 * File:   DynaQPrioritizedSweeping.h
 * Author: jandres
 *
 * Created on June 2, 2014, 11:09 PM
 */

#ifndef DYNAQPRIORITIZEDSWEEPING_H
#define	DYNAQPRIORITIZEDSWEEPING_H

#include "GlobalHeader.h"

#include <cstdint>
#include <set>
#include <map>
#include <queue>
#include <cmath>

#include "StateAction.h"
#include "StateActionTransition.h"
#include "StateActionPairValueComparison.h"
#include "DynaQ.h"

using namespace std;

namespace AI {
  namespace Algorithm {

	/**
	 * DynaQPrioritizeSweeping
	 * <p>Prioritize Sweeping only backs up states that factor the most to
	 * achieving the goal during simulation. This way convergence is achieve
	 * faster. Very useful in large state spaces.</p>
	 *
	 * @note This is currently very slow. An update is being cultivated.
	 *
	 * @see StateActionTransition representing the models.
	 *
	 * @see DynaQ
	 */
	template<class S, class A>
	class DynaQPrioritizeSweeping final: public DynaQ<S, A> {
	  typedef pair<StateAction<S, A>, AI::FLOAT> StateActionPair;

	public:
	  /**
	   * @param stepSize range [0.0, 1.0]. High step size means faster learning, but less precise convergence.
	   * @param discountRate range [0.0, 1.0]. High discount rate means more consideration of future events.
	   * @param simulationIterationCount How many simulation per update.
	   * @param stateTransitionGreediness High value means less likely to choose random action during simulation.
	   * @param stateTransitionStepSize High value means faster learning in models but lower values means more accurate models.
	   */
	  DynaQPrioritizeSweeping(AI::FLOAT stepSize, AI::FLOAT discountRate,
		  Policy<S, A>& policy, AI::UINT simulationIterationCount,
		  AI::FLOAT stateTransitionGreediness, AI::FLOAT stateTransitionStepSize,
		  AI::FLOAT priorityThreshold);

	  virtual void update(const StateAction<S, A>& currentStateAction,
		  const S& nextState, const AI::FLOAT reward,
		  const set<A>& actionSet);

	protected:
	  void _prioritySweep(const set<A>& actionSet);
	  AI::FLOAT _getTDError(const StateAction<S, A>& currentStateAction,
		  const AI::FLOAT reward, const StateAction<S, A>& nextStateAction);
	protected:
	  priority_queue<StateActionPair, std::vector<StateActionPair>,
		  StateActionPairValueComparison<S, A> > _priorityQueue;
	  AI::FLOAT _priorityThreshold;
	};

	template<class S, class A>
	DynaQPrioritizeSweeping<S, A>::DynaQPrioritizeSweeping(AI::FLOAT stepSize,
		AI::FLOAT discountRate, Policy<S, A>& policy,
		AI::UINT simulationIterationCount, AI::FLOAT stateTransitionGreediness,
		AI::FLOAT stateTransitionStepSize, AI::FLOAT priorityThreshold) :
			DynaQ<S, A>(stepSize, discountRate, policy,
						simulationIterationCount, stateTransitionGreediness,
						stateTransitionStepSize),
			_priorityThreshold(priorityThreshold) {
	}

	template<class S, class A>
	void DynaQPrioritizeSweeping<S, A>::_prioritySweep(
		const set<A>& actionSet) {
	  // Repeat n times while priority queue is not empty.
	  for (AI::UINT i = 0; i < this->_simulationIterationCount; i++) {
		if (_priorityQueue.empty())
		  break;

		StateAction<S, A> currentStateActionPair = _priorityQueue.top().first;
		_priorityQueue.pop();

		// Acquire next reward from model.
		const StateActionTransition<S>& currentStateActionTransition =
			this->_model.at(currentStateActionPair);
		const S& nextState = currentStateActionTransition.getNextState();
		AI::FLOAT nextReward = currentStateActionTransition.getReward(
			nextState);

		// Acquire max_action(Q(S, a)).
		A nextAction = this->getLearningAction(nextState, actionSet);

		StateAction<S, A> nextStateAction(nextState, nextAction);

		// Update Q(S, A).
		this->backUpStateActionPair(currentStateActionPair, nextReward,
									nextStateAction);

		for (typename map<StateAction<S, A>, StateActionTransition<S> >::iterator iter =
			this->_model.begin(); iter != this->_model.end(); iter++) {
		  // Acquire a model(S) and look for a model(S) that transition to current(S, A).
		  StateActionTransition<S>& modelStateTransition = iter->second;
		  const S& modelNextState = modelStateTransition.getNextState();

		  // If model(S) -> current(S, A), that means model(S) factors in reaching terminal state.
		  // And because of that, back up model(S).
		  if (modelNextState == currentStateActionPair.getState()) {
			AI::FLOAT priorReward = modelStateTransition.getReward(
				modelNextState);
			A nextModelAction = this->argMax(modelNextState, actionSet);

			AI::FLOAT temptdError = _getTDError(
				iter->first, priorReward,
				StateAction<S, A>(modelNextState, nextModelAction));

			AI::FLOAT tempPriority = abs(temptdError);
			if (tempPriority > _priorityThreshold) {
			  _priorityQueue.push(StateActionPair(iter->first, tempPriority));
			}
		  }
		}
	  }
	}

	template<class S, class A>
	AI::FLOAT DynaQPrioritizeSweeping<S, A>::_getTDError(
		const StateAction<S, A>& currentStateAction, const AI::FLOAT reward,
		const StateAction<S, A>& nextStateAction) {
	  AI::FLOAT tdError =
		  (reward + this->_discountRate
			  * this->_stateActionPairContainer[nextStateAction]
		   - this->_stateActionPairContainer[currentStateAction]);
	  return tdError;
	}

	template<class S, class A>
	void DynaQPrioritizeSweeping<S, A>::update(
		const StateAction<S, A>& currentStateAction, const S& nextState,
		const AI::FLOAT reward, const set<A>& actionSet) {
	  ReinforcementLearning<S, A>::update(currentStateAction, nextState, reward,
										  actionSet);

	  // Update model.
	  this->_updateModel(currentStateAction, nextState, reward);

	  // Acquire A', and tdError.
	  A nextAction = this->argMax(nextState, actionSet);
	  AI::FLOAT tdError = _getTDError(currentStateAction, reward,
								   StateAction<S, A>(nextState, nextAction));

	  // Acquire priority value.
	  AI::FLOAT priority = abs(tdError);
	  if (priority > _priorityThreshold) {
		_priorityQueue.push(StateActionPair(currentStateAction, priority));
	  }

	  // Repeat n times while priority queue is not empty.
	  _prioritySweep(actionSet);
	}
  } /* namespace Algorithm */
} /* namespace AI */
#endif	/* DYNAQ_H */

