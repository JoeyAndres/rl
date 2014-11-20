/*
 * SensorStatesDiscrete.h
 *
 *  Created on: Jun 17, 2014
 *      Author: jandres
 */

#ifndef SENSORSTATESDISCRETE_H_
#define SENSORSTATESDISCRETE_H_

#include "SensorBase.h"

using namespace std;

namespace AI {

/*! \class SensorDiscrete
 *  \brief Base class for sensors of discrete nature.
 *  \tparam S State data type that is discrete, e.g. AI::UINT,
 *          AI::INT, etc.
 *
 *  Base class for sensors of discrete nature.
 */
template<class S, class A>
class SensorDiscrete : public SensorBase<S, A> {
 public:
  SensorDiscrete(Environment<S, A>& env);
  
  // Overriden methods.
  virtual bool isTerminalState(const S& stateData) const;
  
 public:  
  /**
   * @param terminalData new terminal state to be added.
   */
  virtual void addTerminalState(const S& terminalData);

 private:
  set<S> _terminalStates;  // Must know when to stop.
};

template<class S, class A>
SensorDiscrete<S, A>::SensorDiscrete(Environment<S, A>& env) :
    SensorBase<S, A>(env){
}

template<class S, class A>
bool SensorDiscrete<S, A>::isTerminalState(
    const S& stateData) const {
  return _terminalStates.find(stateData) != _terminalStates.end();
}

template<class S, class A>
void SensorDiscrete<S, A>::addTerminalState(
    const S& terminalData) {
  _terminalStates.insert(terminalData);
}

} /* namespace AI */

#endif /* SENSORSTATESDISCRETE_H_ */
