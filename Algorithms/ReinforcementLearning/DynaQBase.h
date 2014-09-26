/*
 * DynaQa.h
 *
 *  Created on: Jun 14, 2014
 *      Author: jandres
 */

#ifndef DYNAQBASE_H_
#define DYNAQBASE_H_

#include <map>
#include <utility>
#include <tuple>
#include <boost/thread/shared_mutex.hpp>

#include "StateActionTransition.h"

using namespace std;

namespace AI {
  namespace Algorithm {
	template<class S, class A>
	class DynaQBase {
	public:
	  DynaQBase(AI::UINT simulationIterationCount,
		  AI::FLOAT stateTransitionGreediness, AI::FLOAT stateTransitionStepSize);

	  virtual void backUpStateActionPair(
		  const StateAction<S, A>& currentStateAction, const FLOAT reward,
		  const StateAction<S, A>& nextStateActionPair) = 0;
	  virtual A argMax(const S& state, const set<A>& actionSet) const = 0;
	protected:
	  virtual void _updateModel(const StateAction<S, A>& currentStateAction,
		  const S& nextState, const FLOAT reward);

	  virtual void _addModelSafe(const StateAction<S, A>& currentStateAction);
	  virtual void _addModel(const StateAction<S, A>& currentStateAction);

	  virtual void _simulate(const set<A>& actionSet);
	protected:
	  AI::UINT _simulationIterationCount;
	  map<StateAction<S, A>, StateActionTransition<S> > _model;
	  AI::FLOAT _stateActionTransitionGreediness;
	  AI::FLOAT _stateActionTransitionStepSize;

	  boost::shared_mutex _generalLock;  // General Lock.
	  boost::shared_mutex _modelLock;
	};
  } /* namespace Algorithm */
} /* namespace AI */

template<class S, class A>
inline AI::Algorithm::DynaQBase<S, A>::DynaQBase(
	AI::UINT simulationIterationCount, AI::FLOAT stateTransitionGreediness,
	AI::FLOAT stateTransitionStepSize) :
		_simulationIterationCount(simulationIterationCount),
		_stateActionTransitionGreediness(stateTransitionGreediness),
		_stateActionTransitionStepSize(stateTransitionStepSize) {
}

template<class S, class A>
void AI::Algorithm::DynaQBase<S, A>::_updateModel(
	const StateAction<S, A>& currentStateAction, const S& nextState,
	const FLOAT reward) {
  boost::unique_lock<boost::shared_mutex> generalLock(_generalLock);
  boost::unique_lock<boost::shared_mutex> modellLock(_modelLock);
  _addModel(currentStateAction);
  StateActionTransition<S> &st = _model.at(currentStateAction);
  st.update(nextState, reward);
}

template<class S, class A>
void AI::Algorithm::DynaQBase<S, A>::_addModelSafe(
	const StateAction<S, A>& currentStateAction) {
  boost::unique_lock<boost::shared_mutex> modellLock(_modelLock);
  _addModel(currentStateAction);
}

template<class S, class A>
inline void AI::Algorithm::DynaQBase<S, A>::_addModel(
	const StateAction<S, A>& currentStateAction) {
  _model.emplace(
	  std::piecewise_construct,
	  std::make_tuple(currentStateAction),
	  std::make_tuple(_stateActionTransitionGreediness,
					  _stateActionTransitionStepSize));
}

template<class S, class A>
void AI::Algorithm::DynaQBase<S, A>::_simulate(
	const set<A>& actionSet) {
  if (_model.empty())
	return;

  for (AI::UINT i = 0; i < _simulationIterationCount; i++) {
	// Pick a random state in _model.
	typename map<StateAction<S, A>, StateActionTransition<S> >::const_iterator item =
		_model.begin();
	std::advance(item, rand() % _model.size());

	const StateActionTransition<S>& st = _model.at(item->first);

	const S& transState = st.getNextState();

	A nextAction = argMax(transState, actionSet);

	backUpStateActionPair(item->first, st.getReward(transState),
						  StateAction<S, A>(transState, nextAction));
  }
}

#endif /* DYNAQBASE_H_ */
