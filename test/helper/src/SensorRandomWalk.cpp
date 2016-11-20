/**
 * SensorRandomWalk.cpp
 */

#include "../include/SensorRandomWalk.h"
#include "../include/RandomWalkEnvironment.h"

namespace rl {
namespace agent {

SensorRandomWalk::SensorRandomWalk() :
  SensorDiscrete<INT>(spState<INT>(new INT(RandomWalkEnvironment::State::B))) {
}

}
}
