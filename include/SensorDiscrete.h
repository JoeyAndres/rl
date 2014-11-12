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
 *  \tparam SensorData State data type that is discrete, e.g. AI::UINT,
 *          AI::INT, etc.
 *
 *  Base class for sensors of discrete nature.
 */
template<class SensorData>
class SensorDiscrete : public SensorBase<SensorData> {
 public:
  // Overriden methods.
  virtual bool isState(const SensorData& state) const;
  virtual bool isTerminalState(const SensorData& stateData) const;

 public:
  /**
   * @return set of currently observed states.
   */
  virtual const set<SensorData>& getObservedStates() const;

  /**
   * @param terminalData new terminal state to be added.
   */
  virtual void addTerminalState(const SensorData& terminalData);

  /**
   * @param sensorData adds a new observed sensor data.
   */
  virtual void addSensorData(const SensorData& sensorData);

 private:
  set<SensorData> _sensorData;  // Keep track of the observed states.
  set<SensorData> _terminalStates;  // Must know when to stop.
};
} /* namespace AI */

template<class SensorData>
const set<SensorData>& AI::SensorDiscrete<SensorData>::getObservedStates() const {
  return this->_sensorData;
}

template<class SensorData>
bool AI::SensorDiscrete<SensorData>::isTerminalState(
    const SensorData& stateData) const {
  return _terminalStates.find(stateData) != _terminalStates.end();
}

template<class SensorData>
void AI::SensorDiscrete<SensorData>::addSensorData(
    const SensorData& sensorData) {
  _sensorData.insert(sensorData);
}

template<class SensorData>
void AI::SensorDiscrete<SensorData>::addTerminalState(
    const SensorData& terminalData) {
  // Ensure terminal state is also in _sensorData.
  addSensorData(terminalData);
  _terminalStates.insert(terminalData);
}

template<class SensorData>
bool AI::SensorDiscrete<SensorData>::isState(const SensorData& state) const {
  return _sensorData.find(state) != _sensorData.end();
}

#endif /* SENSORSTATESDISCRETE_H_ */
