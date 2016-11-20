/*
 * SensorStatesDiscrete.h
 *
 *  Created on: Jun 17, 2014
 *      Author: jandres
 */

#ifndef SENSORSTATESDISCRETE_H_
#define SENSORSTATESDISCRETE_H_

#include "Sensor.h"

using namespace std;

namespace rl {
namespace agent {

/*! \class SensorDiscrete
 *  \brief Base class for sensors of discrete nature.
 *  \tparam S State data type that is discrete, e.g. rl::UINT,
 *          rl::INT, etc.
 *
 *  Base class for sensors of discrete nature.
 */
template<class S>
class SensorDiscrete : public Sensor<S> {
 public:
  using Sensor<S>::Sensor;

  virtual bool isTerminalState(const spState<S> &stateData) const override;

  /**
   * @param terminalData new terminal state to be added.
   */
  virtual void addTerminalState(const spState<S> &terminalData);

 private:
  spStateSet<S> _terminalStates;  // Must know when to stop.
};

template<class S>
bool SensorDiscrete<S>::isTerminalState(
  const spState<S> &stateData) const {
  return _terminalStates.find(stateData) != _terminalStates.end();
}

template<class S>
void SensorDiscrete<S>::addTerminalState(
  const spState<S> &terminalData) {
  _terminalStates.insert(terminalData);
}

}  // namespace agent
}  /* namespace rl */

#endif /* SENSORSTATESDISCRETE_H_ */
