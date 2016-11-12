//
// Created by jandres on 12/11/16.
//

#pragma once

#include <set>

using namespace std;

namespace AI {

/*!\class ActionSet
 * \brief Utility class for storing Action.
 *
 * \tparam A Action data type.
 */
template<class A>
class ActionSet {
 public:
  /**
   * No-arg constractor. Creates an empty set of action.
   */
  ActionSet();

  /**
   * @param actionData Initial set of action.
   */
  ActionSet(const set<A>& actionData);

  /**
 * @return set of actions.
 */
  const set <A> &getActionSet() const;

  /**
   * @param data A to be added.
   */
  void addAction(const A &data);

  /**
   * @param dataSet replace the action set with a new one.
   */
  void setActionSet(set <A> dataSet);

 protected:
  set <A> _actionData;

};

template<class A>
ActionSet<A>::ActionSet() {}

template<class A>
ActionSet<A>::ActionSet(const set<A>& actionData) : _actionData(actionData) {}

template<class A>
void ActionSet<A>::addAction(const A &data) {
  _actionData.insert(data);
}

template<class A>
const set<A> &ActionSet<A>::getActionSet() const {
  return _actionData;
}

template<class A>
void ActionSet<A>::setActionSet(set <A> dataSet) {
  _actionData = dataSet;
}
}  // namespace AI
