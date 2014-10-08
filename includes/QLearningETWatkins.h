/* 
 * File:   QLearningETWatkinsETWatkins.h
 * Author: jandres
 *
 * Created on June 7, 2014, 8:22 AM
 */

#ifndef QLEARNINGETWATKINS_H
#define	QLEARNINGETWATKINS_H

#include <set>
#include <map>

#include "StateAction.h"
#include "EligibilityTraces.h"
#include "Policy.h"
#include "QLearning.h"

using std::set;
using std::map;

namespace AI {
namespace Algorithm {

/**
 * QLearningETWatkins
 * @see QLearning
 * @see EligibilityTraces
 */
template<class S, class A>
class QLearningETWatkins final: public EligibilityTraces<S, A>,
		public QLearning<S, A> {
public:
	QLearningETWatkins(AI::FLOAT stepSize, AI::FLOAT discountRate,
			Policy<S, A>& policy, AI::FLOAT lambda);

	/**
	 * Update the stateAction map.
	 * @param currentState
	 * @param currentAction
	 * @param nextState
	 * @param currentStateActionValue Value of currentState and currentAction.
	 * @param stateAction A map of StateAction to Value.
	 * @param actionSet A set of all actions.
	 * @return next action to be executed.
	 */
	virtual void update(const StateAction<S, A>& currentStateAction,
			const S& nextState, const AI::FLOAT currentStateActionValue,
			const set<A>& actionSet);
private:

};

template<class S, class A>
void QLearningETWatkins<S, A>::update(
		const StateAction<S, A>& currentStateAction, const S& nextState,
		const AI::FLOAT reward, const set<A>& actionSet) {
	ReinforcementLearning<S, A>::update(currentStateAction, nextState, reward,
			actionSet);
	EligibilityTraces<S, A>::_eligibilityTraces.insert(
			std::pair<StateAction<S, A>, AI::FLOAT>(currentStateAction, 0.0F));
	A nextAction = this->getLearningAction(nextState, actionSet);

	this->_updateEligibilityTraces(currentStateAction,
			StateAction<S, A>(nextState, nextAction), reward,
			this->_stateActionPairContainer, this->_stepSize,
			this->_discountRate);
}

template<class S, class A>
QLearningETWatkins<S, A>::QLearningETWatkins(AI::FLOAT stepSize,
		AI::FLOAT discountRate, Policy<S, A>& policy, AI::FLOAT lambda) :
		EligibilityTraces<S, A>(lambda), QLearning<S, A>(stepSize, discountRate,
				policy) {
}
}
}

#endif	/* QLEARNINGETWATKINS_H */

