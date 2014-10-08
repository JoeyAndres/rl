/* 
 * File:   EpsilonGreedy.h
 * Author: jandres
 *
 * Created on June 6, 2014, 6:11 PM
 */

#ifndef EPSILONGREEDY_H
#define	EPSILONGREEDY_H

#include "GlobalHeader.h"

#include <random>
#include <random>

#include "Policy.h"
#include "StateAction.h"

using namespace std;

namespace AI {
namespace Algorithm {

template<class S, class A>
class EpsilonGreedy: public Policy<S, A> {
public:
	EpsilonGreedy(AI::FLOAT greediness);
	virtual ~EpsilonGreedy();

	/**
	 * Returns the action that will "likely" gives the highest reward from the current state.
	 * @param state the state to apply the argMax to.
	 * @param stateAction map of StateAction to value.
	 * @param actionSet a set of possible actions.
	 * @return the action that will "likely" gives the highest reward.
	 */
	const A& argMax(const map<A, AI::FLOAT>& actionValues,
			const set<A>& actionSet) const;

	virtual const A& getAction(const map<A, AI::FLOAT>& actionValues,
			const set<A>& actionSet);

	/**
	 * @param greediness
	 */
	void setGreediness(AI::FLOAT greediness);

	/**
	 * @return current greediness.
	 */
	AI::FLOAT getGreediness() const;
protected:
	random_device _randomDevice;
	uniform_real_distribution<AI::FLOAT> _distribution;
	AI::FLOAT _greediness;
};

typedef EpsilonGreedy<vector<AI::FLOAT>, vector<AI::FLOAT> > EpsilonGreedySL;
}
}

template<class S, class A>
AI::Algorithm::EpsilonGreedy<S, A>::EpsilonGreedy(AI::FLOAT greediness) :
		_greediness(greediness), _distribution(0.0F, 1.0F) {
}

template<class S, class A>
AI::Algorithm::EpsilonGreedy<S, A>::~EpsilonGreedy() {
}

template<class S, class A>
const A& AI::Algorithm::EpsilonGreedy<S, A>::getAction(
		const map<A, AI::FLOAT>& actionValues, const set<A>& actionSet) {
	const AI::FLOAT& r = _distribution(_randomDevice);
	if (r > _greediness) {
		uniform_int_distribution<AI::INT> indexDistribution(0,
				actionSet.size());
		typename set<A>::const_iterator it(actionSet.begin());
		advance(it, indexDistribution(_randomDevice));
		return (*it);
	} else {
		return argMax(actionValues, actionSet);
	}
}

template<class S, class A>
const A& AI::Algorithm::EpsilonGreedy<S, A>::argMax(
		const map<A, AI::FLOAT>& actionValues, const set<A>& actionSet) const {
	auto maxActionIter = actionSet.begin();
	for (auto iter = actionSet.begin(); iter != actionSet.end(); iter++) {
		if (actionValues.at(*iter) > actionValues.at(*maxActionIter)) {
			maxActionIter = iter;
		}
	}

	return (*maxActionIter);
}

template<class S, class A>
void AI::Algorithm::EpsilonGreedy<S, A>::setGreediness(AI::FLOAT greediness) {
	this->_greediness = greediness;
}

template<class S, class A>
AI::FLOAT AI::Algorithm::EpsilonGreedy<S, A>::getGreediness() const {
	return _greediness;
}

#endif	/* EPSILONGREEDY_H */

