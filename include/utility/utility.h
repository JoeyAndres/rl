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

#include <map>
#include <utility>
#include <algorithm>

using std::pair;

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

}  // namespace utility
}  // namespace rl
