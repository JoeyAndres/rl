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

#include <cstdlib>
#include <cstdint>
#include <vector>

#include "../declares.h"

using std::vector;

namespace rl {
namespace hash {

/*! \class HashInterface
 *  \brief Interface for all hash encapsulation.
 *  \tparam RET return data type.
 */
template<class RET>
class HashInterface {
 public:
  /**
   * @param byteArray
   * @param len
   * @return h(byteArray)
   */
  virtual RET hash(const rl::BYTE * const byteArray, size_t len) = 0;
  virtual RET hash(const vector<rl::BYTE>& byteArray) = 0;
};

}  // namespace hash
}  // namespace rl
