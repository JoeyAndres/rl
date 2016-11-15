/* 
 * File:   StateActionPairValueComparison.h
 * Author: jandres
 *
 * Created on June 8, 2014, 12:18 AM
 */

#ifndef STATEACTIONPAIRVALUECOMPARISON_H
#define	STATEACTIONPAIRVALUECOMPARISON_H

#include "../declares.h"

#include <map>

#include "StateAction.h"

using namespace std;

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
} /* rl */

#endif	/* STATEACTIONPAIRVALUECOMPARISON_H */
