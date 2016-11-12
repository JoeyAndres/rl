/* 
 * File:   StateActionPairContainer.h
 * Author: jandres
 *
 * Created on June 2, 2014, 12:59 PM
 */

#ifndef STATEACTIONPAIRCONTAINER_H
#define	STATEACTIONPAIRCONTAINER_H

#include "GlobalHeader.h"

#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <mutex>

#include "StateAction.h"
#include "Observer.h"
#include "StateActionNotExistException.h"
#include "utility.h"

using namespace std;

namespace AI {

/*! \class StateActionPairContainer
 *  \brief Encapsulates the mapping of StateAction to their Value.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 */
template<class S, class A>
class StateActionPairContainer {
 public:
  /**
   * no-arg constructor.
   */
  StateActionPairContainer();

  /**
   * Adds a new state. Note that in order to avoid overwriting
   * @param state State to be added.
   * @param value Value of the state to be added.
   * @param actionArray
   */
  virtual void addState(const S& state, AI::FLOAT value,
                        const set<A>& actionSet);

  /**
   * Adds a new action.
   * @param action
   * @param value
   * @param actionSet
   */
  virtual void addAction(A& action, AI::FLOAT value, const set<S>& actionSet);

  /**
   * @param state to be search in the _stateActionPairMap.
   * @return true if state is in _stateActionPairMap.
   */
  virtual bool stateInStateActionPairMap(const S& state,
                                         const set<A>& actionSet) const;

  /**
   * @param stateAction
   * @return the value of stateAction.
   * @throws StateActionNotEistException when stateAction does not exist.
   */
  virtual const AI::FLOAT& getStateActionValue(
      const StateAction<S, A>& stateAction) const
          throw (StateActionNotExistException);

  /**
   * \f$ map[stateAction] \Leftarrow value \f$.
   * @param stateAction to set the value of.
   * @param value value of stateAction.
   * @throw StateActionNoExistException stateAction given does not exist.
   */
  virtual void setStateActionValue(const StateAction<S, A>& stateAction,
                                   AI::FLOAT value)
                                       throw (StateActionNotExistException);

  /**
   * Access state-action value via [] operator.
   * @param stateAction StateActionPairContainer[stateAction]
   * @return StateActionPairContainer[stateAction] value.
   */
  const AI::FLOAT& operator[](const StateAction<S, A>& stateAction) const;

  /**
   * @return begin iterator of state-action to value map.
   */
  typename map<StateAction<S, A>, AI::FLOAT>::const_iterator begin() const;

  /**
   * @return end iterator of state-action to value map.
   */
  typename map<StateAction<S, A>, AI::FLOAT>::const_iterator end() const;

  /**
   * @return The state-action pair to reward map.
   */
  const map<StateAction<S, A>, AI::FLOAT>& getMap() const;

  /**
   * @return A multimap in which the entry are organized by the reward (from least to greatest).
   */
  multimap<AI::FLOAT, StateAction<S, A>> getReverseMap() const;

 protected:
  map<StateAction<S, A>, AI::FLOAT> _stateActionPairMap;  //!< state-action -> value mapping.
};

template<class S, class A>
StateActionPairContainer<S, A>::StateActionPairContainer() {
}

template<class S, class A>
void StateActionPairContainer<S, A>::addState(const S& state, AI::FLOAT value,
                                              const set<A>& actionSet) {
  for (const A& action : actionSet) {
    _stateActionPairMap.insert(
        std::pair<StateAction<S, A>, AI::FLOAT>(
            StateAction<S, A>(state, action), value));
  }
}

template<class S, class A>
void StateActionPairContainer<S, A>::addAction(A& action, AI::FLOAT value,
                                               const set<S>& stateSet) {
  for (const S& state : stateSet) {
    _stateActionPairMap.insert(
        std::pair<StateAction<S, A>, AI::FLOAT>(
            StateAction<S, A>(state, action), value));
  }
}

template<class S, class A>
bool StateActionPairContainer<S, A>::stateInStateActionPairMap(
    const S& state, const set<A>& actionSet) const {
  const A& sampleAction = *(actionSet.begin());
  bool rv = _stateActionPairMap.find(StateAction<S, A>(state, sampleAction))
      != _stateActionPairMap.end();
  return rv;
}
}

template<class S, class A>
inline void AI::StateActionPairContainer<S, A>::setStateActionValue(
    const StateAction<S, A>& stateAction, AI::FLOAT value)
        throw (StateActionNotExistException) {
  try {
    _stateActionPairMap.at(stateAction);
  } catch (const std::out_of_range& oor) {
    StateActionNotExistException exception("State-Pair given is not yet added.");
    throw exception;
  }

  _stateActionPairMap[stateAction] = value;
}

template<class S, class A>
inline const AI::FLOAT& AI::StateActionPairContainer<S, A>::getStateActionValue(
    const StateAction<S, A>& stateAction) const
        throw (StateActionNotExistException) {
  try {
    return _stateActionPairMap.at(stateAction);
  } catch (const std::out_of_range& oor) {
    StateActionNotExistException exception("State-Pair given is not yet added.");
    throw exception;
  }
}

template<class S, class A>
inline const AI::FLOAT& AI::StateActionPairContainer<S, A>::operator [](
    const StateAction<S, A>& stateAction) const {
  return getStateActionValue(stateAction);
}

template<class S, class A>
inline typename map<AI::StateAction<S, A>, AI::FLOAT>::const_iterator AI::StateActionPairContainer<
    S, A>::begin() const {
  return _stateActionPairMap.begin();
}

template<class S, class A>
inline typename map<AI::StateAction<S, A>, AI::FLOAT>::const_iterator AI::StateActionPairContainer<
    S, A>::end() const {
  return _stateActionPairMap.end();
}

template<class S, class A>
inline const map<AI::StateAction<S, A>, AI::FLOAT>& AI::StateActionPairContainer<
  S, A>::getMap() const {
  return this->_stateActionPairMap;
};

template<class S, class A>
inline multimap<AI::FLOAT, AI::StateAction<S, A>> AI::StateActionPairContainer<
  S, A>::getReverseMap() const {
  return AI::Utility::flipMap(this->_stateActionPairMap);
};

#endif	/* STATEACTIONPAIRCONTAINER_H */

