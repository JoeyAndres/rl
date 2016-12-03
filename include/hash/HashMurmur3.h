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

#include <cstdint>
#include <vector>

#include "../declares.h"
#include "HashInterface.h"

using std::vector;

namespace rl {
namespace hash {

/*! \struct HashMurmur3Out
 *  \brief Encapsulates the output of the murmur hash.
 *  Encapsulates the output of the murmur hash. uint64_t hashVal[2] is
 *  the the array being encapsulated since output of murmur3 hash is 128 bit.
 */
struct HashMurmur3Out {
  uint64_t hashVal[2];
};

/*! \class Murmur3
 *  \brief Murmur3 hash encapsulated.
 */
class Murmur3 : public HashInterface<HashMurmur3Out> {
 public:
  virtual HashMurmur3Out hash(const rl::BYTE * const byteArray, size_t len);
  virtual HashMurmur3Out hash(const vector<rl::BYTE>& byteArray);
};

}  // namespace hash
}  // namespace rl
