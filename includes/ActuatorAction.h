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

template<class ActionData>
class Actuator {
 public:
  Actuator();
  Actuator(set<ActionData> dataSet);
  virtual void applyAction(const ActionData& action) = 0;

  const set<ActionData>& getActionSet() const;
  void addAction(const ActionData& data);
  void setActionSet(set<ActionData> dataSet);
 private:
  set<ActionData> _actionData;  // Available action data.
};

template<class ActionData>
AI::Actuator<ActionData>::Actuator() {
}

template<class ActionData>
AI::Actuator<ActionData>::Actuator(set<ActionData> dataSet) {
  _actionData = dataSet;
}

template<class ActionData>
void AI::Actuator<ActionData>::addAction(const ActionData& data) {
  _actionData.insert(data);
}

template<class ActionData>
const set<ActionData>& AI::Actuator<ActionData>::getActionSet() const {
  return _actionData;
}

template<class ActionData>
void AI::Actuator<ActionData>::setActionSet(set<ActionData> dataSet) {
  _actionData = dataSet;
}

} /* namespace AI */

#endif /* ACTUATOR_H_ */
