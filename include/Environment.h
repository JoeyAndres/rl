/*
 * Environment.h
 *
 *  Created on: Nov 16, 2014
 *      Author: jandres
 */

#ifndef INCLUDE_ENVIRONMENT_H_
#define INCLUDE_ENVIRONMENT_H_

namespace AI {

template <class S, class A, class R>
/*! \class Environment
 * \brief Root Class for all Environment.
 */
class Environment {
 public:
  Environment();
  virtual ~Environment();

  virtual const void getLastObservedtState() const = 0;
  virtual const void getLastObservedReward() const = 0;
 protected:
};

template <class S, class A, class R>
Environment<S, A, R>::Environment(){
}

template <class S, class A, class R>
Environment<S, A, R>::~Environment(){
}

} /* namespace AI */

#endif /* INCLUDE_ENVIRONMENT_H_ */
