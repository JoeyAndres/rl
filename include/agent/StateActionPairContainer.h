/**
 * rl - Reinforcement Learning
 * Copyright (C) 2016  Joey Andres<yeojserdna@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <map>
#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>

#include "../declares.h"
#include "../utility/utility.h"
#include "StateAction.h"
#include "StateActionNotExistException.h"

using std::map;
using std::multimap;

namespace rl {
namespace agent {

/*! \class StateActionPairContainer
 *  \brief Encapsulates the mapping of StateAction to their Value.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 */
template<
    class S,
    class A,

    template<
      class Key,
      class T,
      class Compare = std::less<Key>,
      class Allocator = std::allocator<std::pair<const Key, T>>
    >
    class SA_MAP = map>
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
  virtual void addState(const spState<S> &state, FLOAT value,
                        const spActionSet<A> &actionSet);

  /**
   * Adds a new state with the corresponding action.
   * @param stateAction State and corresponding action to be added.
   * @param value The value of the stateAction.
   */
  virtual void addStateAction(const StateAction<S, A> &stateAction,
                              FLOAT value);

  /**
   * Adds a new action.
   * @param action
   * @param value
   * @param actionSet
   */
  virtual void addAction(const spAction<A> &action, FLOAT value,
                         const spStateSet<S> &stateSet);

  /**
   * @param state to be search in the _stateActionPairMap.
   * @return true if state is in _stateActionPairMap.
   */
  virtual bool stateInStateActionPairMap(const spState<S> &state,
                                         const spActionSet<A> &actionSet) const;

  /**
   * @param stateAction
   * @return the value of stateAction.
   * @throws StateActionNotEistException when stateAction does not exist.
   */
  virtual const FLOAT getStateActionValue(
    const StateAction<S, A> &stateAction) const
  throw(StateActionNotExistException);

  /**
   * \f$ map[stateAction] \Leftarrow value \f$.
   * @param stateAction to set the value of.
   * @param value value of stateAction.
   * @throw StateActionNoExistException stateAction given does not exist.
   */
  virtual void setStateActionValue(const StateAction<S, A> &stateAction,
                                   FLOAT value);

  /**
   * Access state-action value via [] operator.
   * @param stateAction StateActionPairContainer[stateAction]
   * @return StateActionPairContainer[stateAction] value.
   *
   * Note: Although we can add the stateAction if it doesn't exist,
   *       I don't want this program to pass when something is deeply wrong
   *       stateAction pair is never added in the first place.
   */
  FLOAT operator[](const StateAction<S, A> &stateAction) const
  throw(StateActionNotExistException);

  /**
   * @return begin iterator of state-action to value map.
   */
  typename SA_MAP<StateAction<S, A>, FLOAT>::const_iterator begin() const;

  /**
   * @return end iterator of state-action to value map.
   */
  typename SA_MAP<StateAction<S, A>, FLOAT>::const_iterator end() const;

  /**
   * @return state-action pair count.
   */
  size_t size() const;

 protected:
  /*! \var _stateActionPairMap
   *  A mapping of state-action to value.
   */
  SA_MAP<StateAction<S, A>, FLOAT> _stateActionPairMap;
};

template<class S, class A>
using StateActionPairContainerSimple = StateActionPairContainer<S, A, std::map>;

template<
    class S,
    class A,
    template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>> class SA_MAP>
StateActionPairContainer<S, A, SA_MAP>::StateActionPairContainer() {
}

template<
    class S,
    class A,
    template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>> class SA_MAP>
void StateActionPairContainer<S, A, SA_MAP>::addState(
  const spState<S> &state,
  FLOAT value,
  const spActionSet<A> &actionSet) {
  for (auto action : actionSet) {
    _stateActionPairMap.insert(
      std::pair<StateAction<S, A>, FLOAT>(
        StateAction<S, A>(state, action), value));
  }
}

template<
    class S,
    class A,
    template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>> class SA_MAP>
void StateActionPairContainer<S, A, SA_MAP>::addStateAction(
  const StateAction<S, A> &stateAction,
  FLOAT value) {
  this->_stateActionPairMap.insert(
    std::pair<StateAction<S, A>, FLOAT>(stateAction, value));
}

template<
    class S,
    class A,
    template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>> class SA_MAP>
void StateActionPairContainer<S, A, SA_MAP>::addAction(
    const spAction<A> &action,
    FLOAT value,
    const spStateSet<S> &stateSet) {
  for (auto state : stateSet) {
    _stateActionPairMap.insert(
      std::pair<StateAction<S, A>, FLOAT>(
        StateAction<S, A>(state, action), value));
  }
}

template<
    class S,
    class A,
    template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>> class SA_MAP>
bool StateActionPairContainer<S, A, SA_MAP>::stateInStateActionPairMap(
  const spState<S> &state, const spActionSet<A> &actionSet) const {
  const spAction<A> &sampleAction = *(actionSet.begin());
  bool rv = _stateActionPairMap.find(StateAction<S, A>(state, sampleAction))
    != _stateActionPairMap.end();
  return rv;
}

template<
    class S,
    class A,
    template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>> class SA_MAP>
void StateActionPairContainer<S, A, SA_MAP>::setStateActionValue(
  const StateAction<S, A> &stateAction, FLOAT value) {
  _stateActionPairMap[stateAction] = value;
}

template<
    class S,
    class A,
    template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>> class SA_MAP>
const FLOAT StateActionPairContainer<S, A, SA_MAP>::getStateActionValue(
  const StateAction<S, A> &stateAction) const
throw(StateActionNotExistException) {
  try {
    return _stateActionPairMap.at(stateAction);
  } catch (const std::out_of_range &oor) {
#ifdef DEBUG
    std::cerr << "State-Pair given is not yet added. "
              << __FILE__ ":" << __LINE__
              << std::endl;
#endif
    StateActionNotExistException exception(
      "State-Pair given is not yet added.");
    throw exception;
  }
}

template<
    class S,
    class A,
    template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>> class SA_MAP>
FLOAT StateActionPairContainer<S, A, SA_MAP>::operator[](
  const StateAction<S, A> &stateAction) const
throw(StateActionNotExistException) {
  return getStateActionValue(stateAction);
}

template<
    class S,
    class A,
    template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>> class SA_MAP>
typename SA_MAP<StateAction<S, A>, FLOAT>::const_iterator
StateActionPairContainer<S, A, SA_MAP>::begin() const {
  return _stateActionPairMap.begin();
}

template<
    class S,
    class A,
    template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>> class SA_MAP>
typename SA_MAP<StateAction<S, A>, FLOAT>::const_iterator
StateActionPairContainer<S, A, SA_MAP>::end() const {
  return _stateActionPairMap.end();
}

template<
    class S,
    class A,
    template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>> class SA_MAP>
size_t StateActionPairContainer<S, A, SA_MAP>::size() const {
  return this->_stateActionPairMap.size();
}

}  // namespace agent
}  // namespace rl
