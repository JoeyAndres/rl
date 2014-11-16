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
#include <shared_mutex>

#include "StateActionTransition.h"

using namespace std;

namespace AI {
namespace Algorithm {
namespace RL {

/*! \class DynaQBase
 *  \brief Abstract base class for DynaQ algorithms.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 *
 *  DynaQ algorithm is a QLearning algorithm that employs a <i>model</i>
 *  to "model" the environment. Thus, in every update, the algorithm can
 *  do \f$n\f$ simulations, enabling faster convergence to "optimal" policy.
 */
template<class S, class A>
class DynaQBase {
 public:
  /**
   * @param simulationIterationCount number of simulations per update/backup.
   * @param stateTransitionGreediness greediness in selecting highest value model.
   * @param stateTransitionStepSize how fast does a model update a value of a
   *                                state-action pair.
   */
  DynaQBase(AI::UINT simulationIterationCount,
            AI::FLOAT stateTransitionGreediness,
            AI::FLOAT stateTransitionStepSize);

 protected:
  /**
   * Note that this is just a place-holder, since this will be aggregate
   * backup implementations in children.
   * \f$ Q[S, A] \leftarrow Q[S, A] + \alpha\times [R + \gamma \times max_{A'}Q[S', A'] - Q[S, A] ]\f$
   * @param currentStateAction \f$(S, A)\f$, current state-action pair.
   * @param reward \f$R\f$, reward after \f$(S, A)\f$.
   * @param nextStateActionPair \f$(S', A')\f$, next state-action pair.
   */
  virtual void backUpStateActionPair(
      const StateAction<S, A>& currentStateAction, const FLOAT reward,
      const StateAction<S, A>& nextStateActionPair) = 0;

  /**
   * Note that this is just a place-holder, since this will be aggregate
   * argMax implementations in children.
   * Returns the action that will most "likely" gives the highest reward from the
   * current state.
   * @param state the state to apply the argMax to.
   * @param stateAction map of StateAction to value.
   * @param actionSet a set of possible actions.
   * @return the action that will "likely" gives the highest reward.
   */
  virtual A argMax(const S& state, const set<A>& actionSet) const = 0;

  /**
   * Update the stateAction map.
   * @param currentState currentState agent is in.
   * @param currentAction action taken by agent by being in currentState.
   * @param nextState nextState by taking currentAction in currentState.
   * @param reward reward of currentStateAction.
   * @param actionSet A set of all actions.
   */
  virtual void _updateModel(const StateAction<S, A>& currentStateAction,
                            const S& nextState, const FLOAT reward);

  /**
   * Adds new stateAction pair to the model with mutex lock.
   * @param currentStateAction state-action pair to be added.
   */
  virtual void _addModelSafe(const StateAction<S, A>& currentStateAction);

  /**
   * Adds new stateAction pair to the model without mutex lock.
   * @param currentStateAction state-action pair to be added.
   */
  virtual void _addModel(const StateAction<S, A>& currentStateAction);

  /**
   * Performs simulation _simulationIterationCount times.
   * @param actionSet set of actions of agent.
   */
  virtual void _simulate(const set<A>& actionSet);

 protected:
  AI::UINT _simulationIterationCount;  //!< Number of simulation, the higher the value
                                       //!< the faster the convergence, but the slower
                                       //!< each time step takes.

  /*! \var _model
   *  These are where model is stored. Specifically, for each state-action
   *  pair, and their possible transistion states, encapsulated by StateActionTransition
   *  class.
   */
  map<StateAction<S, A>, StateActionTransition<S> > _model;

  AI::FLOAT _stateActionTransitionGreediness;  //!< How likely does the model picks
                                               //!< an action that will generate highest
                                               //!< value given a state.
  AI::FLOAT _stateActionTransitionStepSize;  //!< How fast does the model increment the
                                             //!< state-action value.

  std::shared_timed_mutex _generalLock;  //!< Mutex lock for everything else that is not a model.
  std::shared_timed_mutex _modelLock;  //!< Mutex lock for model.
};

template<class S, class A>
inline DynaQBase<S, A>::DynaQBase(
    AI::UINT simulationIterationCount, AI::FLOAT stateTransitionGreediness,
    AI::FLOAT stateTransitionStepSize)
    : _simulationIterationCount(simulationIterationCount),
      _stateActionTransitionGreediness(stateTransitionGreediness),
      _stateActionTransitionStepSize(stateTransitionStepSize) {
}

template<class S, class A>
void DynaQBase<S, A>::_updateModel(
    const StateAction<S, A>& currentStateAction, const S& nextState,
    const FLOAT reward) {
  std::unique_lock < std::shared_timed_mutex > generalLock(_generalLock);
  std::unique_lock < std::shared_timed_mutex > modellLock(_modelLock);
  _addModel(currentStateAction);
  StateActionTransition<S> &st = _model.at(currentStateAction);
  st.update(nextState, reward);
}

template<class S, class A>
void DynaQBase<S, A>::_addModelSafe(
    const StateAction<S, A>& currentStateAction) {
  std::unique_lock < std::shared_timed_mutex > modellLock(_modelLock);
  _addModel(currentStateAction);
}

template<class S, class A>
inline void DynaQBase<S, A>::_addModel(
    const StateAction<S, A>& currentStateAction) {
  _model.emplace(
      std::piecewise_construct,
      std::make_tuple(currentStateAction),
      std::make_tuple(_stateActionTransitionGreediness,
                      _stateActionTransitionStepSize));
}

template<class S, class A>
void DynaQBase<S, A>::_simulate(const set<A>& actionSet) {
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

} /* namespace RL */
} /* namespace Algorithm */
} /* namespace AI */

#endif /* DYNAQBASE_H_ */
