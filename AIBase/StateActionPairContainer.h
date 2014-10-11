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
#include <boost/thread/shared_mutex.hpp>

#include "StateAction.h"
#include "Observer.h"
#include "StateActionNotExistException.h"

using namespace std;

namespace AI {

template<class S, class A>
class StateActionPairContainer {
 public:
  StateActionPairContainer();

  /**
   * Adds a new state. Note that in order to avoid overwriting
   * @see stateInStateActionPairMap().
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

  virtual void setStateActionValue(const StateAction<S, A>& stateAction,
                                   AI::FLOAT value)
                                       throw (StateActionNotExistException);

  const AI::FLOAT& operator[](const StateAction<S, A>& stateAction) const;
  typename map<StateAction<S, A>, AI::FLOAT>::const_iterator begin() const;
  typename map<StateAction<S, A>, AI::FLOAT>::const_iterator end() const;
 protected:
  map<StateAction<S, A>, AI::FLOAT> _stateActionPairMap;
  mutable boost::shared_mutex _stateActionPairMapMutex;
};

template<class S, class A>
StateActionPairContainer<S, A>::StateActionPairContainer() {
}

template<class S, class A>
void StateActionPairContainer<S, A>::addState(const S& state, AI::FLOAT value,
                                              const set<A>& actionSet) {
  boost::unique_lock < boost::shared_mutex > saLock(_stateActionPairMapMutex);
  for (const A& action : actionSet) {
    _stateActionPairMap.insert(
        std::pair<StateAction<S, A>, AI::FLOAT>(
            StateAction<S, A>(state, action), value));
  }
}

template<class S, class A>
void StateActionPairContainer<S, A>::addAction(A& action, AI::FLOAT value,
                                               const set<S>& stateSet) {
  boost::unique_lock < boost::shared_mutex > saLock(_stateActionPairMapMutex);
  for (const S& state : stateSet) {
    _stateActionPairMap.insert(
        std::pair<StateAction<S, A>, AI::FLOAT>(
            StateAction<S, A>(state, action), value));
  }
}

// TODO: Due to the elimination of AI::FLOAT reward, get rid of the third paramter EVERYWHERE.

template<class S, class A>
bool StateActionPairContainer<S, A>::stateInStateActionPairMap(
    const S& state, const set<A>& actionSet) const {
  boost::shared_lock < boost::shared_mutex > saLock(_stateActionPairMapMutex);
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
  boost::unique_lock < boost::shared_mutex > saLock(_stateActionPairMapMutex);
  try {
    _stateActionPairMap.at(stateAction);
  } catch (const std::out_of_range& oor) {
    std::cerr << "Out of Range error: " << oor.what() << '\n';
    StateActionNotExistException exception(
        "State-Pair given is not yet added.");
    throw exception;
  }

  _stateActionPairMap[stateAction] = value;
}

template<class S, class A>
inline const AI::FLOAT& AI::StateActionPairContainer<S, A>::getStateActionValue(
    const StateAction<S, A>& stateAction) const
        throw (StateActionNotExistException) {
  boost::shared_lock < boost::shared_mutex > saLock(_stateActionPairMapMutex);
  try {
    return _stateActionPairMap.at(stateAction);
  } catch (const std::out_of_range& oor) {
    std::cerr << "Out of Range error: " << oor.what() << '\n';
    StateActionNotExistException exception(
        "State-Pair given is not yet added.");
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
  boost::shared_lock < boost::shared_mutex > saLock(_stateActionPairMapMutex);
  return _stateActionPairMap.begin();
}

template<class S, class A>
inline typename map<AI::StateAction<S, A>, AI::FLOAT>::const_iterator AI::StateActionPairContainer<
    S, A>::end() const {
  boost::shared_lock < boost::shared_mutex > saLock(_stateActionPairMapMutex);
  return _stateActionPairMap.end();
}

#endif	/* STATEACTIONPAIRCONTAINER_H */

