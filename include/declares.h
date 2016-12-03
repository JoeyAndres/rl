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
#include <set>
#include <memory>
#include <map>
#include <iostream>
#include <utility>

#define DEBUG

#ifndef DEBUG
#define NDEBUG  // Gets rid of assertions.
#endif

namespace rl {

typedef double FLOAT;  //!< Default floating type.
typedef uint64_t UINT;  //!< Default unsigned integer type.
typedef int64_t INT;  //!< Default signed integer type.
typedef uint8_t BYTE;  //!< Byte type.

const FLOAT DEFAULT_GREEDINESS_LEARNING_POLICY = 1.0F;

// Hashing constants.
const UINT MURMUR_HASH_SEED = 0x666;

/**
 * TODO(jandres): Add this to some factory generated module that sets settings.
 */
const UINT MAX_EPISODES = 100000;

/*! \typedef FEATURE_VECTOR
 *  Feature vector is a data structure for Tile Coding. It is the indices
 *  that contains the data points to be sampled.
 *
 *  TODO(jandres): See #RL-14
 */
typedef std::vector<UINT> FEATURE_VECTOR;

/*! \typedef floatFector
 *  \brief A vector of float.
 *
 *  TODO(jandres): See #RL-14
 */
using floatVector = std::vector<FLOAT>;

/*! \typedef spFloatVector
 *  \brief Wraps floatVector in shared_ptr.
 *
 *  TODO(jandres): See #RL-14
 */
using spFloatVector = std::shared_ptr<std::vector<FLOAT>>;

/*! \typedef StateAndReward
 *  \tparam S data type of the State.
 *
 *  Represent the pair of state and the corresponding reward.
 */
template<class S>
using StateAndReward = std::pair<S, FLOAT>;

/*! \typedef spState
 *  \tparam S data type of the State.
 *
 *  Wraps states in shared_ptr. This makes development easier since
 *  as we pass the states around, we are guaranteed they still exist.
 */
template<class S>
using spState = std::shared_ptr<S>;

/*! \typedef spStateComp
 *  \tparam S data type of the State.
 *
 *  Comparison for spState should be by the value they dereference,
 *  not their pointer address value.
 */
template <class S>
class spStateComp {
 public:
  bool operator()(const spState<S>& x, const spState<S>& y) const {
    return *x < *y;
  }
};

/*! \typedef spAction
 *  \tparam A data data type of the action.
 *
 *  Wraps states in shared_ptr. This makes development easier since
 *  as we pass the action around, we are guaranteed they still exist.
 */
template<class A>
using spAction = std::shared_ptr<A>;

/*! \typedef spActionComp
 *  \tparam A data type of the action.
 *
 * Comparison for spAction should be by the value they dereference,
 * not their pointer address value.
 */
template <class A>
class spActionComp {
 public:
  bool operator()(const spAction<A>& x, const spAction<A>& y) const {
    return *x < *y;
  }
};

/*! \typedef stateCont
 *  \brief State for Gradient descent learning.
 *
 *  TODO(jandres): See #RL-14
 */
typedef std::vector<FLOAT> stateCont;  //!< State container.

/*! \typedef actionCont
 *  \brief Action for Gradient descent learning.
 *
 *  TODO(jandres): See #RL-14
 */
typedef std::vector<FLOAT> actionCont;  //!< Action container.

/*! \typedef spStateCont
 *  \brief Wraps stateCont in shared_ptr.
 */
using spStateCont = spState<stateCont>;

/*! \typedef spActionCont
 *  \brief Wraps actionCont in shared_ptr.
 */
using spActionCont = spState<actionCont>;

/*! \typedef spStateAndReward
 *  \brief A pair of spState and its corresponding reward.
 */
template<class S>
using spStateAndReward = std::pair<spState<S>, FLOAT>;

/*! \typedef spStateXMap
 *  \tparam S data type of state.
 *  \tparam X data type of arbitrary data spState is mapping to.
 *  \brief A mapping of spState to some arbitrary data.
 */
template<class S, class X>
using spStateXMap = std::map<spState<S>, X, spStateComp<S>>;

/*! \typedef spStateSet
 *  \tparam S data type of the state.
 *  \brief A set of spState with an appropriate comparison object.
 */
template<class S>
using spStateSet = std::set<spState<S>, spStateComp<S>>;

/*! \typedef spActionSet
 *  \tparam A data type of the action.
 *  \brief A set of spAction with an appropriate comparison object.
 */
template<class A>
using spActionSet = std::set<spAction<A>, spActionComp<A>>;

/*! \typedef spActionValueMap
 *  \param A data type of the action.
 *  \brief A map of spAction<A> and it's corresponding value.
 */
template <class A>
using spActionValueMap = std::map<spAction<A>, FLOAT, spActionComp<A>>;

}  // namespace rl

