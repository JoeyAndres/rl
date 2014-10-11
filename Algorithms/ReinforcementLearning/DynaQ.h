/*
 * File:   DynaQ.h
 * Author: jandres
 *
 * Created on June 2, 2014, 11:09 PM
 */

#ifndef DYNAQ_H
#define	DYNAQ_H

#include <cstdint>
#include <set>
#include <map>
#include <thread>
#include <mutex>

#include "StateAction.h"
#include "StateActionTransition.h"
#include "ReinforcementLearning.h"
#include "DynaQRLMP.h"

using namespace std;

namespace AI {
namespace Algorithm {

/**
 * DynaQ
 * <p>The DynaQ algorithm is a subclass of Reinforcement Algorithm.
 * DynaQ employs simulationCount for every update thus improving
 * the conversion rate.</p>
 *
 * @see StateActionTransition representing the models.
 */
template<class S, class A>
class DynaQ : public DynaQRLMP<S, A> {
 public:
  /**
   * @param stepSize range [0.0, 1.0]. High step size means faster learning, but less precise convergence.
   * @param discountRate range [0.0, 1.0]. High discount rate means more consideration of future events.
   * @param simulationIterationCount How many simulation per update.
   * @param stateTransitionGreediness High value means less likely to choose random action during simulation.
   * @param stateTransitionStepSize High value means faster learning in models but lower values means more accurate models.
   */
  DynaQ(AI::FLOAT stepSize, AI::FLOAT discountRate, Policy::Policy<S, A>& policy,
        AI::UINT simulationIterationCount, AI::FLOAT stateTransitionGreediness,
        AI::FLOAT stateTransitionStepSize);

  virtual void update(const StateAction<S, A>& currentStateAction,
                      const S& nextState, const FLOAT reward,
                      const set<A>& actionSet);
};
}
/* namespace Algorithm */
} /* namespace AI */

template<class S, class A>
AI::Algorithm::DynaQ<S, A>::DynaQ(AI::FLOAT stepSize, AI::FLOAT discountRate,
                                  Policy::Policy<S, A>& policy,
                                  AI::UINT simulationIterationCount,
                                  AI::FLOAT stateTransitionGreediness,
                                  AI::FLOAT stateTransitionStepSize)
    : DynaQRLMP<S, A>(stepSize, discountRate, policy, simulationIterationCount,
                      stateTransitionGreediness, stateTransitionStepSize) {
}

template<class S, class A>
void AI::Algorithm::DynaQ<S, A>::update(
    const StateAction<S, A>& currentStateAction, const S& nextState,
    const FLOAT reward, const set<A>& actionSet) {
  ReinforcementLearning<S, A>::update(currentStateAction, nextState, reward,
                                      actionSet);
  A nextAction = this->getLearningAction(nextState, actionSet);
  this->backUpStateActionPair(currentStateAction, reward,
                              StateAction<S, A>(nextState, nextAction));

// Update model.
  this->_updateModel(currentStateAction, nextState, reward);

// Simulation.
  this->_simulate(actionSet);
}

#endif	/* DYNAQ_H */

