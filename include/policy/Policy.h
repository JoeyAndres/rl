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
#include "../agent/StateAction.h"

using std::shared_ptr;

namespace rl {
namespace policy {

/*! \class Policy
 *  \brief Base class for all Policy.
 *
 *  Policy sets the rule for action selection given a mapping of action to
 *  action values and a set of action.
 *
 *  \tparam S State data type.
 *  \tparam A Action data type.
 */
template<class S, class A>
class Policy {
 public:
  /**
   * Returns <b>action</b> given a mapping of actions and their value and a
   * set of actions.
   *
   * @param actionValues a mapping of actions to their corresponding value.
   * @param actionSet set of actions.
   * @return <b>action</b> given a mapping of actions and their value and a
   *         set of actions.
   */

  virtual spAction<A> getAction(
    const spActionValueMap<A>& actionValues,
    const spActionSet<A>& actionSet) = 0;

    /**
   * Returns <b>action</b> given a mapping of actions and their value and a
   * set of actions.
   *
   * @param actionValues a mapping of actions to their corresponding value.
   * @param actionSet set of actions.
   * @param action with maximum value.
   * @return <b>action</b> given a mapping of actions and their value and a
   *         set of actions.
   */
  virtual spAction<A> getAction(const spActionValueMap<A>& actionValues,
                                const spActionSet<A>& actionSet,
                                const rl::spAction<A>& maxAction) = 0;
};

/*! \typedef spPolicy
 *
 *  Policy wrapped in smart pointer.
 */
template<class S, class A>
using spPolicy = shared_ptr<Policy<S, A>>;

}  // namespace policy
}  // namespace rl
