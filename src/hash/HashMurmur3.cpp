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

#include "declares.h"  // NOLINT
#include "hash/HashMurmur3.h"
#include "murmur3/MurmurHash3.h"

namespace rl {
namespace hash {

HashMurmur3Out Murmur3::hash(const rl::BYTE *const byteArray,
                                                  size_t len) {
  HashMurmur3Out out;
  MurmurHash3_x64_128(&byteArray[0], len * sizeof(rl::BYTE),
                      rl::MURMUR_HASH_SEED, &(out.hashVal[0]));
  return out;
}

HashMurmur3Out Murmur3::hash(const vector<rl::BYTE>& msg) {
  HashMurmur3Out out;
  MurmurHash3_x64_128(&msg[0], msg.size() * sizeof(rl::BYTE),
                      rl::MURMUR_HASH_SEED, &(out.hashVal[0]));
  return out;
}

}  // namespace hash
}  // namespace rl
