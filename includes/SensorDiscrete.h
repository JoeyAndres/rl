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
template<class SensorData>
class SensorStatesDiscrete : public SensorBase<SensorData> {
 public:
  virtual const set<SensorData>& getObservedStates() const;
  virtual void addTerminalState(const SensorData& terminalData);
  virtual void addSensorData(const SensorData& sensorData);
  virtual bool isState(const SensorData& state) const;
  virtual bool isTerminalState(const SensorData& stateData) const;
 private:
  set<SensorData> _sensorData;  // Keep track of the observed states.
  set<SensorData> _terminalStates;  // Must know when to stop.
};
} /* namespace AI */

template<class SensorData>
const set<SensorData>& AI::SensorStatesDiscrete<SensorData>::getObservedStates() const {
  return this->_sensorData;
}

template<class SensorData>
bool AI::SensorStatesDiscrete<SensorData>::isTerminalState(
    const SensorData& stateData) const {
  return _terminalStates.find(stateData) != _terminalStates.end();
}

template<class SensorData>
void AI::SensorStatesDiscrete<SensorData>::addSensorData(
    const SensorData& sensorData) {
  _sensorData.insert(sensorData);
}

template<class SensorData>
void AI::SensorStatesDiscrete<SensorData>::addTerminalState(
    const SensorData& terminalData) {
  // Ensure terminal state is also in _sensorData.
  addSensorData(terminalData);
  _terminalStates.insert(terminalData);
}

template<class SensorData>
bool AI::SensorStatesDiscrete<SensorData>::isState(
    const SensorData& state) const {
  return _sensorData.find(state) != _sensorData.end();
}

#endif /* SENSORSTATESDISCRETE_H_ */
