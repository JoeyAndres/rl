/* 
 * File:   Policy.h
 * Author: jandres
 *
 * Created on June 6, 2014, 5:48 PM
 */

#ifndef POLICY_H
#define	POLICY_H

#include "declares.h"

#include <map>
#include <vector>

#include "StateAction.h"

using namespace std;

namespace AI {
namespace Algorithm {
namespace Policy {

/*! \class Policy
 *  \brief Base class for all Policy.
 *
 *  Policy sets the rule for action selection given a mapping of action to
 *  action values and a set of action.
 *
 *  \tparam S State data type.
 *  \tparam A Action data type.
 */
template<class S, class A>
class Policy {
 public:
  /**
   * Returns <b>action</b> given a mapping of actions and their value and a
   * set of actions.
   *
   * @param actionValues a mapping of actions to their corresponding value.
   * @param actionSet set of actions.
   * @return <b>action</b> given a mapping of actions and their value and a
   *         set of actions.
   */
  virtual A getAction(const map<A, AI::FLOAT>& actionValues,
                             const set<A>& actionSet) = 0;

    /**
   * Returns <b>action</b> given a mapping of actions and their value and a
   * set of actions.
   *
   * @param actionValues a mapping of actions to their corresponding value.
   * @param actionSet set of actions.
   * @param action with maximum value.
   * @return <b>action</b> given a mapping of actions and their value and a
   *         set of actions.
   */
  virtual A getAction(const map<A, AI::FLOAT>& actionValues,
                      const set<A>& actionSet, const A& maxAction) = 0;
 private:

};

/*! \typedef PolicySL
 *  \brief Policy for Supervised Learning.
 *
 *  Since supervised learning usually involves multi-dimensional state space
 *  and action space, PolicySL is a typedef of Policy specifically for that
 *  purpose.
 */
typedef Policy<STATE_CONT, ACTION_CONT> PolicySL;

} /* Policy */
} /* Algorithm */
} /* AI */

#endif	/* POLICY_H */

