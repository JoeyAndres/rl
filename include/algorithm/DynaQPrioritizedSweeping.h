/*
 * File:   DynaQPrioritizedSweeping.h
 * Author: jandres
 *
 * Created on June 2, 2014, 11:09 PM
 */

#ifndef DYNAQPRIORITIZEDSWEEPING_H
#define	DYNAQPRIORITIZEDSWEEPING_H

#include "../declares.h"

#include <cstdint>
#include <set>
#include <map>
#include <queue>
#include <cmath>

#include "../agent/StateAction.h"
#include "../agent/StateActionTransition.h"
#include "../agent/StateActionPairValueComparison.h"
#include "DynaQ.h"

using namespace std;

namespace rl {
namespace algorithm {

/*! \DynaQPrioritizeSweeping
 *  \brief DynaQ Prioritize sweeping implementation.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 *
 *  Prioritize Sweeping only backs up states that factor the most to
 *  achieving the goal during simulation. This way convergence is achieve
 *  faster. Very useful in large state spaces.
 *
 * @note This is currently very slow. An update is being cultivated.
 */
template<class S, class A>
class DynaQPrioritizeSweeping final: public DynaQ<S, A> {
  typedef pair<StateAction<S, A>, rl::FLOAT> StateActionPair;

 public:
  /**
   * @param stepSize range \f$[0.0, 1.0]\f$. High step size means faster learning, but
   * less precise convergence.
   * @param discountRate range \f$[0.0, 1.0]\f$. High discount rate means more
   * consideration of future events.
   * @param policy online policy, that is policy used for action selection.
   * @param simulationIterationCount number of simulations per update/backup.
   * @param stateTransitionGreediness greediness in selecting highest value model.
   * @param stateTransitionStepSize how fast does a model update a value of a
   *                                state-action pair.
   * @param priorityThreshold range \f$[0.0, 1.0]\f$, a low value means don't sweep
   *                          too far back. A high priority means sweep far back.
   */
  DynaQPrioritizeSweeping(rl::FLOAT stepSize, rl::FLOAT discountRate,
                          policy::Policy<S, A>& policy,
                          rl::UINT simulationIterationCount,
                          rl::FLOAT stateTransitionGreediness,
                          rl::FLOAT stateTransitionStepSize,
                          rl::FLOAT priorityThreshold);

  virtual void update(const StateAction<S, A>& currentStateAction,
                      const spState<S>& nextState, const rl::FLOAT reward,
                      const spActionSet<A>& actionSet) override;

 protected:
  void _prioritySweep(const spActionSet<A>& actionSet);
  rl::FLOAT _getTDError(const StateAction<S, A>& currentStateAction,
                        const rl::FLOAT reward,
                        const StateAction<S, A>& nextStateAction);
 protected:
  priority_queue<StateActionPair, std::vector<StateActionPair>,
                 StateActionPairValueComparison<S, A> > _priorityQueue;
  rl::FLOAT _priorityThreshold;
};

template<class S, class A>
DynaQPrioritizeSweeping<S, A>::DynaQPrioritizeSweeping(
  rl::FLOAT stepSize, rl::FLOAT discountRate, policy::Policy<S, A>& policy,
  rl::UINT simulationIterationCount, rl::FLOAT stateTransitionGreediness,
  rl::FLOAT stateTransitionStepSize, rl::FLOAT priorityThreshold)
  : DynaQ<S, A>(stepSize, discountRate, policy, simulationIterationCount,
                stateTransitionGreediness, stateTransitionStepSize),
    _priorityThreshold(priorityThreshold) {
}

template<class S, class A>
void DynaQPrioritizeSweeping<S, A>::_prioritySweep(const spActionSet<A>& actionSet) {
  // Repeat n times while priority queue is not empty.
  for (rl::UINT i = 0; i < this->_simulationIterationCount; i++) {
    if (_priorityQueue.empty())
      break;

    StateAction<S, A> currentStateActionPair = _priorityQueue.top().first;
    _priorityQueue.pop();

    // Acquire next reward from model.
    const StateActionTransition<S>& currentStateActionTransition = this->_model
      .at(currentStateActionPair);
    auto nextState = currentStateActionTransition.getNextState();
    rl::FLOAT nextReward = currentStateActionTransition.getReward(nextState);

    // Acquire max_action(Q(S, a)).
    auto nextAction = this->getLearningAction(nextState, actionSet);

    StateAction<S, A> nextStateAction(nextState, nextAction);

    // Update Q(S, A).
    this->backUpStateActionPair(currentStateActionPair, nextReward,
                                nextStateAction);

    for (typename map<StateAction<S, A>, StateActionTransition<S> >::iterator iter =
      this->_model.begin(); iter != this->_model.end(); iter++) {
      // Acquire a model(S) and look for a model(S) that transition to current(S, A).
      StateActionTransition<S>& modelStateTransition = iter->second;
      auto modelNextState = modelStateTransition.getNextState();

      // If model(S) -> current(S, A), that means model(S) factors in reaching terminal state.
      // And because of that, back up model(S).
      if (modelNextState == currentStateActionPair.getState()) {
        rl::FLOAT priorReward = modelStateTransition.getReward(modelNextState);
        auto nextModelAction = this->argMax(modelNextState, actionSet);

        rl::FLOAT temptdError = _getTDError(
          iter->first, priorReward,
          StateAction<S, A>(modelNextState, nextModelAction));

        rl::FLOAT tempPriority = abs(temptdError);
        if (tempPriority > _priorityThreshold) {
          _priorityQueue.push(StateActionPair(iter->first, tempPriority));
        }
      }
    }
  }
}

template<class S, class A>
rl::FLOAT DynaQPrioritizeSweeping<S, A>::_getTDError(
  const StateAction<S, A>& currentStateAction, const rl::FLOAT reward,
  const StateAction<S, A>& nextStateAction) {
  rl::FLOAT tdError = (reward
    + this->_discountRate * this->_stateActionPairContainer[nextStateAction]
    - this->_stateActionPairContainer[currentStateAction]);
  return tdError;
}

template<class S, class A>
void DynaQPrioritizeSweeping<S, A>::update(
    const StateAction<S, A>& currentStateAction,
    const spState<S>& nextState,
    const rl::FLOAT reward,
    const spActionSet<A>& actionSet) {
  spAction<A> nextAction = this->argMax(nextState, actionSet);
  StateAction<S, A> nextStateAction(nextState, nextAction);

  DynaQ<S, A>::update(currentStateAction, nextState, reward, actionSet);

  // Update model.
  this->_updateModel(currentStateAction, nextState, reward);

  // Acquire A' and tdError.
  rl::FLOAT tdError = _getTDError(currentStateAction, reward, nextStateAction);

  // Acquire priority value.
  rl::FLOAT priority = abs(tdError);
  if (priority > _priorityThreshold) {
    _priorityQueue.push(StateActionPair(currentStateAction, priority));
  }

  // Repeat n times while priority queue is not empty.
  _prioritySweep(actionSet);
}

} /* namespace algorithm */
} /* namespace rl */

#endif	/* DYNAQ_H */

