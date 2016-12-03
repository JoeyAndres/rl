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

#include "../utility/FactoryAbstract.h"
#include "Actuator.h"

namespace rl {
namespace agent {

/*! \class ActuatorFactory
 *  \brief Factory object for Actuator
 *  \see Actuator
 *  \tparam A Action data type.
 */
template<class A>
class ActuatorFactory : public FactoryAbstract<Actuator<A>> {
 public:
  /**
   * Factory creator method.
   * @param actionSet
   */
  explicit ActuatorFactory(const spActionSet<A> &actionSet);
};

template<class A>
ActuatorFactory<A>::ActuatorFactory(const spActionSet<A> &actionSet) {
  this->_instance = spActuator<A>(new Actuator<A>(actionSet));
}

}  // namespace agent
}  // namespace rl
