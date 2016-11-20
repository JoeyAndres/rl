/* 
 * File:   Policy.h
 * Author: jandres
 *
 * Created on June 6, 2014, 5:48 PM
 */

#pragma once

#include <map>
#include <vector>

#include "../declares.h"
#include "../agent/StateAction.h"

using namespace std;

namespace rl {
namespace policy {

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

  virtual spAction<A> getAction(
    const spActionValueMap<A>& actionValues,
    const spActionSet<A>& actionSet) = 0;

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
  virtual spAction<A> getAction(const spActionValueMap<A>& actionValues,
                                const spActionSet<A>& actionSet,
                                const rl::spAction<A>& maxAction) = 0;
 private:

};

/*! \typedef PolicySL
 *  \brief Policy for Supervised Learning.
 *
 *  Since supervised learning usually involves multi-dimensional state space
 *  and action space, PolicySL is a typedef of Policy specifically for that
 *  purpose.
 */
typedef Policy<stateCont, actionCont> PolicySL;

}  // namespace policy
}  // rl
