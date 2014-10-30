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
#include <thread>

#include "DynaQBase.h"
#include "StateActionTransition.h"

namespace AI {
namespace Algorithm {

/*! \class DynaQCCBase
 *  \brief Base class for DynaQ with concurrency for simulation.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 */
template<class S, class A>
class DynaQCCBase : public DynaQBase<S, A> {
 public:
  /**
   * @param simulationIterationCount number of simulations per update/backup.
   * @param stateTransitionGreediness greediness in selecting highest value model.
   * @param stateTransitionStepSize how fast does a model update a value of a
   *                                state-action pair.
   */
  DynaQCCBase(AI::UINT simulationIterationCount,
              AI::FLOAT stateTransitionGreediness,
              AI::FLOAT stateTransitionStepSize);

  /**
   * Where simulation is called via new thread.
   * @param actionSet set of actions.
   * @param localSimulationSteps  How many simulation steps dedicated to this thread.
   */
  virtual void _threadWorker(const set<A>& actionSet,
                             AI::UINT localSimulationSteps);

  /**
   * When adding a new state-action value to the model, make sure to update distribution.
   */
  void _updateDistribution();

 protected:
  // Inherited.

  virtual void _simulate(const set<A>& actionSet);

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
    AI::FLOAT stateTransitionStepSize)
    : DynaQBase<S, A>(simulationIterationCount, stateTransitionGreediness,
                      stateTransitionStepSize),
      _distribution(0, this->_model.size() - 1) {
}

template<class S, class A>
void AI::Algorithm::DynaQCCBase<S, A>::_updateDistribution() {
  _distribution = std::uniform_int_distribution < AI::INT
      > (0, this->_model.size() - 1);
}

template<class S, class A>
inline void AI::Algorithm::DynaQCCBase<S, A>::_simulate(
    const set<A>& actionSet) {
  std::vector<std::thread> threadVector;
  AI::UINT localSimulationSteps = this->_simulationIterationCount / 12;
  _updateDistribution();
  for (AI::INT i = 0; i < 12; i++) {
    threadVector.push_back(
        std::thread(&DynaQCCBase<S, A>::_threadWorker, this, actionSet,
                      localSimulationSteps));
  }

  for (std::thread& t : threadVector) {
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
