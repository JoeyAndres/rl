#include "SensorRandomWalk.h"
#include "RandomWalkEnvironment.h"

AI::SensorRandomWalk::SensorRandomWalk(Environment<AI::INT, AI::INT>& env) :
    AI::SensorDiscrete<AI::INT, AI::INT>(env){  
}
