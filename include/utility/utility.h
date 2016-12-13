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

#include <array>
#include <map>
#include <utility>
#include <algorithm>
#include <bitset>
#include <cstring>  // memcpy

#include "../declares.h"

using std::array;
using std::pair;
using std::bitset;

namespace rl {
namespace utility {

/**
 * @see http://stackoverflow.com/a/5056797
 * @param src
 * @return
 */
template<typename A, typename B>
std::pair<B, A> flip_pair(const std::pair<A, B> &p) {
  return std::pair<B, A>(p.second, p.first);
}

/**
 * Flips an associative container of A,B pairs to B,A pairs
 * @see http://stackoverflow.com/a/5056797
 * @param src
 * @return
 */
template<typename A, typename B,
  template<class, class, class...> class M, class... Args>
std::multimap<B, A> flipMap(const M<A, B, Args...> &src) {
  std::multimap<B, A> dst;
  std::transform(src.begin(), src.end(),
                 std::inserter(dst, dst.begin()),
                 flip_pair<A, B>);
  return dst;
}

/**
 * Converts an array of float to a bitset
 * @tparam D Number of float in float array.
 * @param fv feature vector.
 * @return bitset
 */
template <size_t D>
bitset<D * FLOAT_SIZE> floatArrayToBitset(const floatArray<D>& fv) {
  bitset<D * FLOAT_SIZE> rv;
  union Converter { FLOAT f; uint64_t i; };
  for (size_t d = 0; d < D; d++) {
    size_t dRev = (D - 1) - d;
    Converter c;
    c.f = fv[d];
    bitset<FLOAT_SIZE> tempBitset = c.i;

    for (size_t b = 0; b < tempBitset.size(); b++) {
      rv[FLOAT_SIZE * dRev + b] = tempBitset[b];
    }
  }
  return rv;
}

template <class T, size_t D1, size_t D2>
array<T, D1 + D2> concatArray(const array<T, D1>& a1, const array<T, D2>& a2) {
  array<T, D1 + D2> rv;
  std::copy(a1.begin(),
            a1.end(),
            rv.begin());
  std::copy(a2.begin(),
            a2.end(),
            rv.begin() + a1.size());
  return rv;
}

}  // namespace utility
}  // namespace rl
