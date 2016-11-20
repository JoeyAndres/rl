//
// Created by jandres on 12/11/16.
//

#pragma once

#include <set>

#include "../declares.h"

using namespace std;

namespace rl {
namespace agent {

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
   * @param actionSet Initial set of action.
   */
  ActionSet(const spActionSet<A> &actionSet);

  /**
 * @return set of actions.
 */
  const spActionSet<A> &getActionSet() const;

  /**
   * @param data A to be added.
   */
  void addAction(const rl::spAction<A> &data);

  /**
   * @param dataSet replace the action set with a new one.
   */
  void setActionSet(const spActionSet<A>& dataSet);

 protected:
  spActionSet<A> _actionData;
};

template<class A>
ActionSet<A>::ActionSet() {}

template<class A>
ActionSet<A>::ActionSet(const spActionSet<A> &actionSet) : _actionData(actionSet) {}

template<class A>
void ActionSet<A>::addAction(const spAction<A> &data) {
  _actionData.insert(data);
}

template<class A>
const spActionSet<A> &ActionSet<A>::getActionSet() const {
  return _actionData;
}

template<class A>
void ActionSet<A>::setActionSet(const spActionSet<A>& dataSet) {
  _actionData = dataSet;
}

}  // namespace agent
}  // namespace rl
