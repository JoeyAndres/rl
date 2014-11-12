/*
 * ActuatorRandomWalk.h
 *
 *  Created on: Jun 1, 2014
 *      Author: jandres
 */

#ifndef ACTUATORRANDOMWALK_H_
#define ACTUATORRANDOMWALK_H_

#include "ActuatorBase.h"
#include "GlobalHeader.h"

namespace AI {

template<class ActionData>
class ActuatorRandomWalk final : public ActuatorBase<ActionData> {
 public:
  virtual void applyAction(const ActionData& action) = 0;
};

template<>
class ActuatorRandomWalk<AI::INT> final : public ActuatorBase<AI::INT> {
 public:
  virtual void applyAction(const AI::INT& action);
};

} /* namespace AI */

#endif /* ACTUATORRANDOMWALK_H_ */
