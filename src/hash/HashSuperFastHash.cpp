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

#include "hash/HashSuperFastHash.h"
#include "superfasthash/SuperFastHash.h"

namespace rl {
namespace hash {

rl::INT SuperFastHash::hash(const rl::BYTE * const byteArray, size_t len) {
  return ::SuperFastHash((const char*)(byteArray), len);
}

rl::INT SuperFastHash::hash(const vector<rl::BYTE>& msg) {
  return ::SuperFastHash((const char*)(msg.data()),
                         msg.size() * sizeof(rl::BYTE));
}

}  // namespace hash
}  // namespace rl
