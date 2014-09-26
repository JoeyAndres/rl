/*
 * DynaQCCBase.h
 *
 *  Created on: Jun 14, 2014
 *      Author: jandres
 */

#ifndef DYNAQCCBASE_H_
#define DYNAQCCBASE_H_

#include "GlobalHeader.h"

#include <cstdint>
#include <random>
#include <vector>
#include <boost/thread.hpp>

#include "DynaQBase.h"
#include "StateActionTransition.h"

namespace AI {
  namespace Algorithm {
	template<class S, class A>
	class DynaQCCBase: public DynaQBase<S, A> {
	public:
	  DynaQCCBase(AI::UINT simulationIterationCount,
		  AI::FLOAT stateTransitionGreediness, AI::FLOAT stateTransitionStepSize);
	protected:
	  virtual void _simulate(const set<A>& actionSet);
	  virtual void _threadWorker(const set<A>& actionSet,
		  AI::UINT localSimulationSteps);
	  void _updateDistribution();

	protected:
	  std::random_device _randomDevice;
	  std::uniform_int_distribution<AI::INT> _distribution;
	};

  }
/* namespace Algorithm */
} /* namespace AI */

template<class S, class A>
inline AI::Algorithm::DynaQCCBase<S, A>::DynaQCCBase(
	AI::UINT simulationIterationCount, AI::FLOAT stateTransitionGreediness,
	AI::FLOAT stateTransitionStepSize) :
		DynaQBase<S, A>(simulationIterationCount, stateTransitionGreediness,
						stateTransitionStepSize),
		_distribution(0, this->_model.size() - 1) {
}

template<class S, class A>
void AI::Algorithm::DynaQCCBase<S, A>::_updateDistribution() {
  _distribution = std::uniform_int_distribution<AI::INT>(0,
													 this->_model.size() - 1);
}

template<class S, class A>
inline void AI::Algorithm::DynaQCCBase<S, A>::_simulate(
	const set<A>& actionSet) {
  std::vector<boost::thread> threadVector;
  AI::UINT localSimulationSteps = this->_simulationIterationCount / 12;
  _updateDistribution();
  for (AI::INT i = 0; i < 12; i++) {
	threadVector.push_back(
		boost::thread(&DynaQCCBase<S, A>::_threadWorker, this, actionSet,
					  localSimulationSteps));
  }

  for (boost::thread& t : threadVector) {
	t.join();
  }
  threadVector.clear();
}

template<class S, class A>
inline void AI::Algorithm::DynaQCCBase<S, A>::_threadWorker(
	const set<A>& actionSet, AI::UINT localSimulationSteps) {
  if (this->_model.empty())
	return;
  for (AI::UINT i = 0; i < localSimulationSteps; i++) {
	// Pick a random state in _model.
	this->_modelLock.lock();
	auto item = this->_model.begin();
	std::advance(item, _distribution(_randomDevice));
	const StateActionTransition<S>& st = this->_model.at(item->first);
	const S& transState = st.getNextState();
	this->_modelLock.unlock();

	A nextAction = this->argMax(transState, actionSet);

	this->backUpStateActionPair(item->first, st.getReward(transState),
								StateAction<S, A>(transState, nextAction));
  }
}

#endif /* DYNAQCCBASE_H_ */
