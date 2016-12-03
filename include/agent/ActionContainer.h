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

#include <memory>

#include "../declares.h"

using std::shared_ptr;

namespace rl {
namespace agent {

/*!\class ActionContainer
 * \brief Utility class for storing Action.
 *
 * \tparam A Action data type.
 */
template<class A>
class ActionContainer {
 public:
  /**
   * No-arg constractor. Creates an empty set of action.
   */
  ActionContainer();

  /**
   * @param actionSet Initial set of action.
   */
  explicit ActionContainer(const spActionSet<A> &actionSet);

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

/*! \typedef spActionContainer
 *
 * Wraps ActionContainer with shared_ptr. @see ActionContainer
 *
 * \tparam A Action data type.
 */
template<class A>
using spActionContainer = shared_ptr<ActionContainer<A>>;

template<class A>
ActionContainer<A>::ActionContainer() {}

template<class A>
ActionContainer<A>::ActionContainer(const spActionSet<A> &actionSet)
  : _actionData(actionSet) {
}

template<class A>
void ActionContainer<A>::addAction(const spAction<A> &data) {
  _actionData.insert(data);
}

template<class A>
const spActionSet<A> &ActionContainer<A>::getActionSet() const {
  return _actionData;
}

template<class A>
void ActionContainer<A>::setActionSet(const spActionSet<A>& dataSet) {
  _actionData = dataSet;
}

}  // namespace agent
}  // namespace rl
