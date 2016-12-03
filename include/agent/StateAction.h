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

#include "../declares.h"

namespace rl {
namespace agent {

/*! \class StateAction
 *  \brief Encapsulates state action pair.
 *  \tparam S data type of state.
 *  \tparam A data type of action.
 *
 *  Encapsulates state action pair. This requires both S state and A action
 *  data type to be comparable.
 */
template<class S, class A>
class StateAction {
 public:
  /**
   * No-arg constructor.
   */
  StateAction();

  /**
   * Constructor for state-action pair.
   * @param state of state-action pair.
   * @param action of state-action pair.
   */
  explicit StateAction(const spState<S>& state, const spState<A>& action);

  /**
   * Copy Constructor.
   * @param sa state-action pair to copy.
   */
  StateAction(const StateAction &sa);

  virtual bool operator<(const StateAction<S, A> &stateAction) const;
  virtual bool operator>(const StateAction<S, A> &stateAction) const;
  virtual bool operator<=(const StateAction<S, A> &stateAction) const;
  virtual bool operator>=(const StateAction<S, A> &stateAction) const;
  virtual bool operator==(const StateAction<S, A> &stateAction) const;
  virtual bool operator!=(const StateAction<S, A> &stateAction) const;

  /**
   * @return return state of state-action pair.
   */
  const spState<S> &getState() const;

  /**
   * @return return action of state-action pair.
   */
  const spAction<A> &getAction() const;

  /**
   * @param state set the state of state-action pair.
   */
  void setState(const spState<S> &state);

  /**
   * @param action set the action of state-action pair.
   */
  void setAction(const spAction<A> &action);

 protected:
  spState<S> _state;  //!< State of state-action pair.
  spAction<A> _action;  //!< Action of state-action pair.
};

template<class S, class A>
StateAction<S, A>::StateAction(const spState<S>& state,
                               const spAction<A>& action)
  : _state(state),
    _action(action) {
}

template<class S, class A>
StateAction<S, A>::StateAction(const StateAction &sa)
  : _state(sa._state),
    _action(sa._action) {
}

template<class S, class A>
bool StateAction<S, A>::operator<(const StateAction<S, A> &stateAction) const {
  if (*_state < *(stateAction._state))
    return true;
  if (*_state > *(stateAction._state))
    return false;
  if (*_action < *(stateAction._action))
    return true;
  return false;
}

template<class S, class A>
bool StateAction<S, A>::operator>(const StateAction<S, A> &stateAction) const {
  if (*_state > *(stateAction._state))
    return true;
  if (*_state < *(stateAction._state))
    return false;
  if (*_action > *(stateAction._action))
    return true;
  return false;
}

template<class S, class A>
bool StateAction<S, A>::operator<=(const StateAction<S, A> &stateAction) const {
  return !(*this > stateAction);
}

template<class S, class A>
bool StateAction<S, A>::operator>=(const StateAction<S, A> &stateAction) const {
  return !(*this < stateAction);
}

template<class S, class A>
bool StateAction<S, A>::operator==(const StateAction<S, A> &stateAction) const {
  if (*_state == *(stateAction._state) && *_action == *(stateAction._action)) {
    return true;
  }
  return false;
}

template<class S, class A>
bool StateAction<S, A>::operator!=(const StateAction<S, A> &stateAction) const {
  if (!(*this == stateAction)) {
    return true;
  }
  return false;
}

template<class S, class A>
const spState<S> &StateAction<S, A>::getState() const {
  return this->_state;
}

template<class S, class A>
const spAction<A> &StateAction<S, A>::getAction() const {
  return this->_action;
}

template<class S, class A>
void StateAction<S, A>::setState(const spState<S> &state) {
  _state = state;
}

template<class S, class A>
void StateAction<S, A>::setAction(const spAction<A> &action) {
  _action = action;
}

}  // namespace agent
} /* namespace rl */
