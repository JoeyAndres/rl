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

#include <utility>

#include "../declares.h"
#include "StateAction.h"

using std::pair;

namespace rl {
namespace agent {

/*! \class StateActionPairValueComparison
 *  \brief comparison object for std::map and other containers in need of comparison.
 *  \tparam S State data type.
 *  \tparam A Action data type.
 *
 * Created as a comparison object for StateAction<S, A> and their corresponding
 * Value/Priority. This comparison object is mainly used in std::priority_queue.
 */
template<class S, class A>
class StateActionPairValueComparison {
 public:
  StateActionPairValueComparison();
  bool operator()(const pair<StateAction<S, A>, rl::FLOAT>& lhs,
                  const pair<StateAction<S, A>, rl::FLOAT>& rhs);
};

template<class S, class A>
StateActionPairValueComparison<S, A>::StateActionPairValueComparison() { }

template<class S, class A>
bool StateActionPairValueComparison<S, A>::operator()(
    const pair<StateAction<S, A>, rl::FLOAT>& lhs,
    const pair<StateAction<S, A>, rl::FLOAT>& rhs) {
  if (lhs.first < rhs.first)
    return true;
  else if (lhs.first > rhs.first)
    return false;

  if (lhs.second < rhs.second)
    return true;
  return false;
}

}  // namespace agent
}  // namespace rl
