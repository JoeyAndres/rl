/*
 * Environment.h
 *
 *  Created on: Nov 16, 2014
 *      Author: Joey Andres
 */

#ifndef INCLUDE_ENVIRONMENT_H_
#define INCLUDE_ENVIRONMENT_H_

#include "GlobalHeader.h"

namespace AI {

template <class S, class A>
/*! \class Environment
 * \brief Root Class for all Environment.
 *
 * All Environment class will override this class be itself.
 */
class Environment {
 public:
  Environment();
  virtual ~Environment();

  /**
   * @return last observed state.
   */
  virtual const S& getLastObservedState() const = 0;

  /**
   * @return last observed reward.
   */
  virtual AI::FLOAT getLastObservedReward() const = 0;
  
  /**
   * @param a action to apply.
   */
  virtual AI::FLOAT applyAction(const A& a) = 0;

  /**
   * Called during at the begining of the episode to reset environment
   * information, if any.
   */
  virtual void reset();
 protected: 
};

template <class S, class A>
inline Environment<S, A>::Environment(){
}

template <class S, class A>
inline Environment<S, A>::~Environment(){
}

template <class S, class A>
inline void Environment<S, A>::reset(){
}

} /* namespace AI */

#endif /* INCLUDE_ENVIRONMENT_H_ */
