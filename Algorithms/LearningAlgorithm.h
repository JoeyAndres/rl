/*
 * SearchAlgorithm.h
 *
 *  Created on: May 31, 2014
 *      Author: jandres
 */

#ifndef SEARCHALGORITHM_H_
#define SEARCHALGORITHM_H_

#include "GlobalHeader.h"

#include <map>
#include <set>
#include <memory>

#include "StateAction.h"
#include "EpsilonGreedy.h"

using std::set;
using std::map;

namespace AI {
namespace Algorithm {

/**
 * LearningAlgorithm
 * <p>An abstract class for all algorithm in general.</p>
 */
template<class S, class A>
class LearningAlgorithm {
public:
	LearningAlgorithm(Policy<S, A>& policy);

	/**
	 * Update the stateAction map.
	 * @param currentState
	 * @param currentAction
	 * @param nextState
	 * @param reward reward of currentState and currentAction.
	 * @param stateAction A map of StateAction to Value.
	 * @param actionSet A set of all actions.
	 * @return next action to be executed.
	 */
	virtual void update(const StateAction<S, A>& currentStateAction,
			const S& nextState, const AI::FLOAT reward,
			const set<A>& actionSet) = 0;

	/**
	 * A policy that varies between algorithms.
	 */
	virtual const A& getAction(const S& state, const set<A>& actionSet) = 0;

	/**
	 * Acquire the value of the state action pair. Each algorithm group (rl,
	 * supervised, unsupervised), or specific algorithm (Q, Sarsa, Gradient Descent)
	 * must implement.
	 * @param stateAction
	 * @return Value of stateAction.
	 */
	virtual AI::FLOAT getStateActionValue(
			const StateAction<S, A>& stateAction) = 0;

	/**
	 * @param policy
	 */
	void seControltPolicy(Policy<S, A>& policy);
	Policy<S, A>& getControlPolicy();

	/**
	 * Performs algorithm routines before episode.
	 */
	virtual void reset();

	const AI::FLOAT& getDefaultStateActionValue() const;

	void setDefaultStateActionValue(const AI::FLOAT& defaultStateActionValue);

	void setLearningPolicy(Policy<S, A>& policy);
	const Policy<S, A> & getLearningPolicy() const;

protected:
	const A& _getLearningPolicyAction(const map<A, AI::FLOAT>& actionValueMap,
			const set<A>& actionSet);

protected:
	AI::FLOAT _defaultStateActionValue;
	Policy<S, A>& _controlPolicy;
	Policy<S, A>& _learningPolicy;

protected:
	static EpsilonGreedy<S, A> _defaultLearningPolicy;
};

template<class S, class A>
EpsilonGreedy<S, A> LearningAlgorithm<S, A>::_defaultLearningPolicy(
		AI::DEFAULT_GREEDINESS_LEARNING_POLICY);

template<class S, class A>
LearningAlgorithm<S, A>::LearningAlgorithm(Policy<S, A>& policy) :
		_controlPolicy(policy), _learningPolicy(_defaultLearningPolicy) {
	_defaultStateActionValue = AI::FLOAT();
}

template<class S, class A>
void LearningAlgorithm<S, A>::seControltPolicy(Policy<S, A>& policy) {
	this->_controlPolicy = policy;
}

template<class S, class A>
Policy<S, A>& LearningAlgorithm<S, A>::getControlPolicy() {
	return _controlPolicy;
}

template<class S, class A>
void LearningAlgorithm<S, A>::reset() {

}

template<class S, class A>
inline const AI::FLOAT& LearningAlgorithm<S, A>::getDefaultStateActionValue() const {
	return _defaultStateActionValue;
}

template<class S, class A>
inline void LearningAlgorithm<S, A>::setDefaultStateActionValue(
		const AI::FLOAT& defaultStateActionValue) {
	_defaultStateActionValue = defaultStateActionValue;
}
} /* namespace Algorithm */
} /* namespace AI */

template<class S, class A>
inline void AI::Algorithm::LearningAlgorithm<S, A>::setLearningPolicy(
		Policy<S, A>& policy) {
	_learningPolicy = policy;
}

template<class S, class A>
inline const AI::Algorithm::Policy<S, A>& AI::Algorithm::LearningAlgorithm<S, A>::getLearningPolicy() const {
	return _learningPolicy;
}

template<class S, class A>
inline const A& AI::Algorithm::LearningAlgorithm<S, A>::_getLearningPolicyAction(
		const map<A, AI::FLOAT>& actionValueMap, const set<A>& actionSet) {
	return _learningPolicy.getAction(actionValueMap, actionSet);
}

#endif /* SEARCHALGORITHM_H_ */
