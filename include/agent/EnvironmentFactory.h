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
#include "Environment.h"

namespace rl {
namespace agent {

/*! \class Environment
 *  \brief Factory object for Environment
 *  \see Environment
 *  \tparam S State data type.
 *  \tparam A Action data type.
 */
template<class S, class A>
class EnvironmentFactory : public FactoryAbstract<Environment<S, A>>{
 public:
  /**
   * Factory creator method.
   * @param actionSet
   */
  explicit EnvironmentFactory(const spActuator<A> &actuator,
                              const spSensor<S> &sensor);
};

template<class S, class A>
EnvironmentFactory<S, A>::EnvironmentFactory(const spActuator<A> &actuator,
                                             const spSensor<S> &sensor) {
  this->_instance =
    spEnvironment<S, A>(new Environment<S, A>(actuator, sensor));
}

}  // namespace agent
}  // namespace rl
