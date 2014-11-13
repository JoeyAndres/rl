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

namespace AI {

/*! \class ActuatorBase
 *  \brief Base class and interface for all Actuator objects.
 *  \tparam ActionData Action data type.
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
template<class ActionData>
class ActuatorBase {
 public:
  /**
   * no-arg constructor. Use this if action set is added later.
   * @deprecated
   */
  ActuatorBase();

  /**
   * Constructor for when actions (or some actions) are known.
   * @param dataSet Set of actions.
   */
  ActuatorBase(set<ActionData> dataSet);

  /**
   * Virtual function to be overloaded.
   *
   * @see Actuator Documentation for example.
   *
   * @param action to be applied to environment.
   */
  virtual void applyAction(const ActionData& action) = 0;

  /**
   * @return set of actions.
   */
  const set<ActionData>& getActionSet() const;

  /**
   * @param data ActionData to be added.
   */
  void addAction(const ActionData& data);

  /**
   * @param dataSet replace the action set with a new one.
   */
  void setActionSet(set<ActionData> dataSet);
 private:
  set<ActionData> _actionData;  //!< A set of possible action to be applied to
                                //!< the environment.
};

template<class ActionData>
AI::ActuatorBase<ActionData>::ActuatorBase() {
}

template<class ActionData>
AI::ActuatorBase<ActionData>::ActuatorBase(set<ActionData> dataSet) {
  _actionData = dataSet;
}

template<class ActionData>
void AI::ActuatorBase<ActionData>::addAction(const ActionData& data) {
  _actionData.insert(data);
}

template<class ActionData>
const set<ActionData>& AI::ActuatorBase<ActionData>::getActionSet() const {
  return _actionData;
}

template<class ActionData>
void AI::ActuatorBase<ActionData>::setActionSet(set<ActionData> dataSet) {
  _actionData = dataSet;
}

} /* namespace AI */

#endif /* ACTUATOR_H_ */
