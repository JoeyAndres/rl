/*
 * Actuator.h
 *
 *  Created on: May 31, 2014
 *      Author: jandres
 * 
 */

#ifndef ACTUATOR_H_
#define ACTUATOR_H_

#include <set>

#include "ActionSet.h"

using std::set;

namespace rl {
namespace agent {

/*! \class
 *  \brief Base class and interface for all Actuator objects.
 *  \tparam A Action data type.
 *
 * Base class and interface for all actuator objects. One can override
 * or extend virtual functions here to direct output to environment. For
 * example, consider a line following robot example.
 */
template<class A>
class Actuator : public ActionSet<A> {
 public:
  /**
   * No-arg constructor.
   */
  Actuator();

  /**
   * Constructor for when actions (or some actions) are known.
   * @param actionSet Set of actions.
   */
  Actuator(const spActionSet<A>& actionSet);
};

typedef Actuator<actionCont> ActuatorSL;

template<class A>
Actuator<A>::Actuator() {
}

template<class A>
Actuator<A>::Actuator(const spActionSet<A>& actionSet) : ActionSet<A>(actionSet) {
}

}  // namespace agent
}  // namespace rl

#endif /* ACTUATOR_H_ */
