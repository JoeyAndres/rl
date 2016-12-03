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

namespace rl {
namespace agent {

/*! \class StateInterface
 *  \brief An interface class for States.
 *  \tparam S State data type.
 */
template<class S>
class StateInterface {
 public:
  explicit StateInterface(const spState<S> &value)
    : _value(value) {
  }

  virtual bool operator<(const StateInterface<S> &rhs) const {
    return this->_value < rhs._value;
  }

  virtual bool operator>(const StateInterface<S> &rhs) const {
    return this->_value > rhs._value;
  }

  virtual bool operator<=(const StateInterface<S> &rhs) const {
    return this->_value <= rhs._value;
  }

  virtual bool operator>=(const StateInterface<S> &rhs) const {
    return this->_value >= rhs._value;
  }

  virtual bool operator==(const StateInterface<S> &rhs) const {
    return this->_value == rhs._value;
  }

  virtual bool operator!=(const StateInterface<S> &rhs) const {
    return this->_value != rhs._value;
  }

  virtual StateInterface<S> &operator=(const StateInterface<S> &rhs) {
    if (this == &rhs) {
      return *this;
    }

    this->_value = rhs._value;
    return *this;
  }

  virtual spState<S> &getValue() {
    return this->_value;
  }

  virtual const spState<S> &getValue() const {
    return this->_value;
  }

 protected:
  spState<S> _value;  // Value of this thing.
};

}  // namespace agent
}  // namespace rl
