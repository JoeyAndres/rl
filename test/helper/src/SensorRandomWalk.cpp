/**
 * SensorRandomWalk.cpp
 */

#include "../include/SensorRandomWalk.h"
#include "../include/RandomWalkEnvironment.h"

namespace rl {

SensorRandomWalk::SensorRandomWalk() :
  SensorDiscrete<INT>(RandomWalkEnvironment::State::B){
}

}
