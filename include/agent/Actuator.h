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

#include "ActionContainer.h"

using std::shared_ptr;

namespace rl {
namespace agent {

/*! \class
 *  \brief Base class and interface for all Actuator objects.
 *  \tparam A Action data type.
 *
 * Base class and interface for all actuator objects. One can override
 * or extend virtual functions here to direct output to environment. For
 * example, consider a line following robot example.
 */
template<class A>
class Actuator : public ActionContainer<A> {
 public:
  /**
   * No-arg constructor.
   */
  Actuator();

  /**
   * Constructor for when actions (or some actions) are known.
   * @param actionSet Set of actions.
   */
  explicit Actuator(const spActionSet<A>& actionSet);
};

/*! \typedef spActuator
 *
 * Wraps Actuator with shared_ptr. @see Actuator
 *
 * \tparam A Action data type.
 */
template<class A>
using spActuator = shared_ptr<Actuator<A>>;

template<class A>
Actuator<A>::Actuator() {
}

template<class A>
Actuator<A>::Actuator(const spActionSet<A>& actionSet)
  : ActionContainer<A>(actionSet) {
}

}  // namespace agent
}  // namespace rl
