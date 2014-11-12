#include "SensorRandomWalk.h"
#include "RandomWalkEnvironment.h"

AI::INT AI::SensorRandomWalk<AI::INT>::getSensorState() {
  RandomWalkEnvironment& rwe = RandomWalkEnvironment::getInstance();
  AI::INT currentState = rwe.getCurrentState();
  this->addSensorData(currentState);
  return currentState;
}

AI::FLOAT AI::SensorRandomWalk<AI::INT>::getReward(AI::INT& sensorState)
    throw (StateNotExistException) {
  if (!isState(sensorState))
    return -1;
  if (sensorState == T) {
    return 0;
  }

  return -1;
}
