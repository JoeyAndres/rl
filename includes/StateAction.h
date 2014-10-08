/*
 * StateAction.h
 *
 *  Created on: May 30, 2014
 *      Author: jandres
 */

#ifndef STATEACTION_H_
#define STATEACTION_H_

namespace AI {
template<class S, class A>
class StateAction {
public:
	StateAction();
	StateAction(S state, A action);

	virtual bool operator<(const StateAction<S, A>& stateAction) const;
	virtual bool operator>(const StateAction<S, A>& stateAction) const;
	virtual bool operator<=(const StateAction<S, A>& stateAction) const;
	virtual bool operator>=(const StateAction<S, A>& stateAction) const;
	virtual bool operator==(const StateAction<S, A>& stateAction) const;
	virtual bool operator!=(const StateAction<S, A>& stateAction) const;

	const S& getState() const;
	const A& getAction() const;
	void setState(const S& state);
	void setAction(const A& action);

protected:
	S _state;
	A _action;
};

template<class S, class A>
StateAction<S, A>::StateAction(S state, A action) {
	_state = state;
	_action = action;
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
