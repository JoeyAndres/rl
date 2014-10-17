/*
 * StateAction.h
 *
 *  Created on: May 30, 2014
 *      Author: jandres
 */

#ifndef STATEACTION_H_
#define STATEACTION_H_

namespace AI {

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
  StateAction(S state, A action);

  /**
   * Copy Constructor.
   * @param sa state-action pair to copy.
   */
  StateAction(const StateAction& sa);

  virtual bool operator<(const StateAction<S, A>& stateAction) const;
  virtual bool operator>(const StateAction<S, A>& stateAction) const;
  virtual bool operator<=(const StateAction<S, A>& stateAction) const;
  virtual bool operator>=(const StateAction<S, A>& stateAction) const;
  virtual bool operator==(const StateAction<S, A>& stateAction) const;
  virtual bool operator!=(const StateAction<S, A>& stateAction) const;

  /**
   * @return return state of state-action pair.
   */
  const S& getState() const;

  /**
   * @return return action of state-action pair.
   */
  const A& getAction() const;

  /**
   * @param state set the state of state-action pair.
   */
  void setState(const S& state);

  /**
   * @param action set the action of state-action pair.
   */
  void setAction(const A& action);

 protected:
  S _state;  //!< State of state-action pair.
  A _action;  //!< Action of state-action pair.
};

template<class S, class A>
StateAction<S, A>::StateAction(S state, A action) {
  _state = state;
  _action = action;
}

template<class S, class A>
StateAction<S, A>::StateAction(const StateAction& sa){
  _state = sa._state;
  _action = sa._action;
}

template<class S, class A>
bool StateAction<S, A>::operator<(const StateAction<S, A>& stateAction) const {
  if (_state < stateAction._state)
    return true;
  if (_state > stateAction._state)
    return false;
  if (_action < stateAction._action)
    return true;
  return false;
}

template<class S, class A>
bool StateAction<S, A>::operator>(const StateAction<S, A>& stateAction) const {
  if (_state > stateAction._state)
    return true;
  if (_state < stateAction._state)
    return false;
  if (_action > stateAction._action)
    return true;
  return false;
}

template<class S, class A>
bool StateAction<S, A>::operator<=(const StateAction<S, A>& stateAction) const {
  return !(*this > stateAction);
}

template<class S, class A>
bool StateAction<S, A>::operator>=(const StateAction<S, A>& stateAction) const {
  return !(*this < stateAction);
}

template<class S, class A>
bool StateAction<S, A>::operator==(const StateAction<S, A>& stateAction) const {
  if (_state == stateAction._state && _action == stateAction._action) {
    return true;
  }
  return false;
}

template<class S, class A>
bool StateAction<S, A>::operator!=(const StateAction<S, A>& stateAction) const {
  if (!(*this == stateAction)) {
    return true;
  }
  return false;
}

template<class S, class A>
const S& StateAction<S, A>::getState() const {
  return this->_state;
}

template<class S, class A>
const A& StateAction<S, A>::getAction() const {
  return this->_action;
}

template<class S, class A>
void StateAction<S, A>::setState(const S& state) {
  _state = state;
}

template<class S, class A>
void StateAction<S, A>::setAction(const A& action) {
  _action = action;
}

} /* namespace AI */

#endif /* STATEACTION_H_ */
