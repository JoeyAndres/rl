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
namespace utility {

template<class T>
class IndexAccessorInterface {
 public:
  virtual T& operator[](size_t i);
  virtual T operator[](size_t i) const;

  virtual T& at(size_t i) = 0;
  virtual T at(size_t i) const = 0;
};

template<class T>
T& IndexAccessorInterface<T>::operator[](size_t i) {
  return this->at(i);
}

template<class T>
T IndexAccessorInterface<T>::operator[](size_t i) const {
  return this->at(i);
}

}  // namespace utility
}  // namespace rl
