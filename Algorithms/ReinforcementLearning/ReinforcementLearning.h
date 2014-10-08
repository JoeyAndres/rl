/*
 * ReinforcementLearning.h
 *
 *  Created on: May 31, 2014
 *      Author: jandres
 */

#ifndef REINFORCEMENTLEARNING_H_
#define REINFORCEMENTLEARNING_H_

#include <cstdlib>
#include <set>
#include <map>
#include <iostream>
#include <boost/thread/shared_mutex.hpp>

#include "StateAction.h"
#include "LearningAlgorithm.h"
#include "Policy.h"
#include "StateActionPairContainer.h"

using namespace std;

namespace AI {
namespace Algorithm {

/**
 * Abstract class for all Reinforcement learning algorithms.
 */
template<class S, class A>
class ReinforcementLearning: public LearningAlgorithm<S, A> {
public:
	/**
	 * @param stepSize range [0.0, 1.0]. High step size means faster learning, but less precise convergence.
	 * @param discountRate range [0.0, 1.0]. High discount rate means more consideration of future events.
	 */
	ReinforcementLearning(AI::FLOAT stepSize, AI::FLOAT discountRate,
			Policy<S, A>& policy);

	/**
	 * Returns the action that will "likely" gives the highest reward from the current state.
	 * @param state the state to apply the argMax to.
	 * @param stateAction map of StateAction to value.
	 * @param actionSet a set of possible actions.
	 * @return the action that will "likely" gives the highest reward.
	 */
	A argMax(const S& state, const set<A>& actionSet) const;

	/**
	 * @return current discount rate.
	 */
	virtual AI::FLOAT getDiscountRate() const;

	/**
	 * @param discountRate
	 */
	virtual void setDiscountRate(AI::FLOAT discountRate);

	/**
	 * @return current stepSize.
	 */
	virtual AI::FLOAT getStepSize() const;

	/**
	 * @param stepSize
	 */
	virtual void setStepSize(AI::FLOAT stepSize);

	/**
	 * Acquire the value of the state action pair. Each algorithm group (rl,
	 * supervised, unsupervised), or specific algorithm (Q, Sarsa, Gradient Descent)
	 * must implement.
	 * @param stateAction
	 * @return Value of stateAction.
	 */
	//virtual AI::FLOAT getStateActionValue(const StateAction<S, A>& stateAction) const;
	/**
	 * Does the main back up for all Temporal difference:
	 * Q(S, A) <- Q(S, A) + stepSize*[R + max_action(S', A') - Q(S, A)]
	 * @param currentStateAction
	 * @param currentStateActionValue
	 * @param nextState
	 * @param nextAction
	 * @param stateActionPairValueMap
	 */
	virtual void backUpStateActionPair(
			const StateAction<S, A>& currentStateAction, const AI::FLOAT reward,
			const StateAction<S, A>& nextStateActionPair);

	virtual void update(const StateAction<S, A>& currentStateAction,
			const S& nextState, const AI::FLOAT reward,
			const set<A>& actionSet);

	const A& getAction(const S& currentState, const set<A>& actionSet);
	const A& getLearningAction(const S& currentState, const set<A>& actionSet);

	// TODO: make all AI::FLOAT parameter a ref.
	virtual AI::FLOAT getStateActionValue(const StateAction<S, A>& stateAction);
	virtual void setStateActionValue(const StateAction<S, A>& stateAction,
			const AI::FLOAT& reward);
	const StateActionPairContainer<S, A>& getStateActionPairContainer() const;

	void setStateActionPairContainer(
			const StateActionPairContainer<S, A>& stateActionPairContainer);

protected:
	void _buildActionValueMap(const set<A>& actionSet, const S& currentState,
			map<A, AI::FLOAT>& actionValueMap);
protected:
	AI::FLOAT _stepSize;
	AI::FLOAT _discountRate;
	StateActionPairContainer<S, A> _stateActionPairContainer;

	mutable boost::shared_mutex _generalLock;  // General Lock.
	mutable boost::shared_mutex _containerLock;
	mutable boost::shared_mutex _stepSizeLock;
	mutable boost::shared_mutex _discountRateLock;
};
} /* namespace Algorithm */
} /* namespace AI */

template<class S, class A>
AI::Algorithm::ReinforcementLearning<S, A>::ReinforcementLearning(
		AI::FLOAT stepSize, AI::FLOAT discountRate, Policy<S, A>& policy) :
		LearningAlgorithm<S, A>(policy) {
	_stepSize = stepSize;
	_discountRate = discountRate;
}

template<class S, class A>
A AI::Algorithm::ReinforcementLearning<S, A>::argMax(const S& state,
		const set<A>& actionSet) const {
	A greedAct = *(actionSet.begin());
	AI::FLOAT currentValue = this->_stateActionPairContainer[StateAction<S, A>(
			state, greedAct)];
	for (const A& action : actionSet) {
		AI::FLOAT value = this->_stateActionPairContainer[StateAction<S, A>(
				state, action)];
		if (currentValue < value) {
			currentValue = value;
			greedAct = action;
		}
	}
	return greedAct;
}

template<class S, class A>
inline AI::FLOAT AI::Algorithm::ReinforcementLearning<S, A>::getDiscountRate() const {
	return _discountRate;
}

template<class S, class A>
inline void AI::Algorithm::ReinforcementLearning<S, A>::setDiscountRate(
		AI::FLOAT discountRate) {
	_discountRate = discountRate;
}

template<class S, class A>
inline AI::FLOAT AI::Algorithm::ReinforcementLearning<S, A>::getStepSize() const {
	return _stepSize;
}

template<class S, class A>
inline void AI::Algorithm::ReinforcementLearning<S, A>::setStepSize(
		AI::FLOAT stepSize) {
	_stepSize = stepSize;
}

template<class S, class A>
inline const AI::StateActionPairContainer<S, A>& AI::Algorithm::ReinforcementLearning<
		S, A>::getStateActionPairContainer() const {
	return _stateActionPairContainer;
}

template<class S, class A>
inline void AI::Algorithm::ReinforcementLearning<S, A>::setStateActionPairContainer(
		const StateActionPairContainer<S, A>& stateActionPairContainer) {
	_stateActionPairContainer = stateActionPairContainer;
}

template<class S, class A>
inline void AI::Algorithm::ReinforcementLearning<S, A>::setStateActionValue(
		const StateAction<S, A>& stateAction, const AI::FLOAT& reward) {
	_stateActionPairContainer.setStateActionValue(stateAction, reward);
}

template<class S, class A>
inline const A& AI::Algorithm::ReinforcementLearning<S, A>::getLearningAction(
		const S& currentState, const set<A>& actionSet) {
	_stateActionPairContainer.addState(currentState,
			this->_defaultStateActionValue, actionSet);
	map<A, AI::FLOAT> actionValueMap;
	_buildActionValueMap(actionSet, currentState, actionValueMap);
	return this->_getLearningPolicyAction(actionValueMap, actionSet);
}

template<class S, class A>
void AI::Algorithm::ReinforcementLearning<S, A>::_buildActionValueMap(
		const set<A>& actionSet, const S& currentState,
		map<A, AI::FLOAT>& actionValueMap) {
	for (const A& action : actionSet) {
		actionValueMap[action] = _stateActionPairContainer[StateAction<S, A>(
				currentState, action)];
	}
}

template<class S, class A>
const A& AI::Algorithm::ReinforcementLearning<S, A>::getAction(
		const S& currentState, const set<A>& actionSet) {
	_stateActionPairContainer.addState(currentState,
			this->_defaultStateActionValue, actionSet);
	map<A, AI::FLOAT> actionValueMap;
	_buildActionValueMap(actionSet, currentState, actionValueMap);
	return this->_controlPolicy.getAction(actionValueMap, actionSet);
}

template<class S, class A>
AI::FLOAT AI::Algorithm::ReinforcementLearning<S, A>::getStateActionValue(
		const StateAction<S, A>& stateAction) {
	return _stateActionPairContainer.getStateActionValue(stateAction);
}

template<class S, class A>
void AI::Algorithm::ReinforcementLearning<S, A>::backUpStateActionPair(
		const StateAction<S, A>& currentStateAction, const AI::FLOAT reward,
		const StateAction<S, A>& nextStateActionPair) {
	boost::unique_lock<boost::shared_mutex> containerLock(_containerLock);

	setStateActionValue(currentStateAction,
			getStateActionValue(currentStateAction)
					+ this->_stepSize
							* (reward
									+ this->_discountRate
											* getStateActionValue(
													nextStateActionPair)
									- getStateActionValue(currentStateAction)));
}

// todo: update lock?
template<class S, class A>
void AI::Algorithm::ReinforcementLearning<S, A>::update(
		const StateAction<S, A>& currentStateAction, const S& nextState,
		const AI::FLOAT reward, const set<A>& actionSet) {
	(void) reward;
	_stateActionPairContainer.addState(currentStateAction.getState(),
			this->_defaultStateActionValue, actionSet);
	_stateActionPairContainer.addState(nextState,
			this->_defaultStateActionValue, actionSet);
}

#endif /* REINFORCEMENTLEARNING_H_ */
