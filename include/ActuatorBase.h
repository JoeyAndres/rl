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

using std::set;

#include "Environment.h"
#include "ActionSet.h"

namespace AI {

/*! \class
 *  \brief Base class and interface for all Actuator objects.
 *  \tparam A Action data type.
 *
 * Base class and interface for all actuator objects. One can override
 * or extend virtual functions here to direct output to environment. For
 * example, consider a line following robot example.
 *
 * ### Example:
 *
 * Supposed there is a line following that takes an input from front sensors,
 * and two motors. Actuator class is concerned with the two motors. One can then
 * create a class by inheriting from Actuator,
 *
 * \code{.cpp}
 * class LineFollowing : public Actuator<std::pair<AI::FLOAT, AI::FLOAT> > {
 *    LineFollowing(set<std::pair<AI::FLOAT, AI::FLOAT> > dataSet);  // Old constructor.
 *    LineFollowing(AI::FLOAT lowerSpeed, AI::FLOAT upperSpeed);  // New constructor.
 *    virtual void applyAction(const std::pair<AI::FLOAT, AI::FLOAT>& action);
 * }
 * \endcode
 *
 * The overridden applyAction is the method responsible for communicating directly to motor
 * drivers, where speed of each motor is given in pairs of two floats.
 */
template<class S, class A>
class ActuatorBase : public ActionSet<A> {
 public:
  /**
   * no-arg constructor. Use this if action set is added later.
   * @deprecated
   */
  ActuatorBase(Environment<S, A>& env);

  /**
   * Constructor for when actions (or some actions) are known.
   * @param dataSet Set of actions.
   */
  ActuatorBase(Environment<S, A>& env, set<A> dataSet);

  /**
   * @see Actuator Documentation for example.  
   * @param action to be applied to environment.
   */
  virtual void applyAction(const A& action);

 private:
  Environment<S, A>& _env; //!< Aggregate environment.
};

typedef ActuatorBase<STATE_CONT, ACTION_CONT> ActuatorSL;

template<class S, class A>
AI::ActuatorBase<S, A>::ActuatorBase(Environment<S, A>& env) : _env(env){}

template<class S, class A>
AI::ActuatorBase<S, A>::ActuatorBase(Environment<S, A>& env, set<A> dataSet) :
    ActionSet<A>(dataSet), _env(env) {}

template<class S, class A>
void AI::ActuatorBase<S, A>::applyAction(const A& action){
  _env.applyAction(action);
}

} /* namespace AI */

#endif /* ACTUATOR_H_ */
