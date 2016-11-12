/**
 * SensorRandomWalk.cpp
 */

#include "../include/SensorRandomWalk.h"
#include "../include/RandomWalkEnvironment.h"

AI::SensorRandomWalk::SensorRandomWalk(Environment<AI::INT, AI::INT>& env) :
    AI::SensorDiscrete<AI::INT, AI::INT>(env){  
}
