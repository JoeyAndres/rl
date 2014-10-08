/*
 * HashUNH.h
 *
 *  Created on: Jun 16, 2014
 *      Author: jandres
 */

#ifndef HASHUNH_H_
#define HASHUNH_H_

#include "GlobalHeader.h"

#include <cstdint>
#include <vector>

using namespace std;

namespace AI {
namespace Algorithm {
AI::INT hashUNH(AI::INT *coordinates, AI::INT numIndices, size_t memorySize);
AI::INT hashUNH(vector<AI::INT>& coordinateVector, size_t memorySize);
} /* Algorithm */
} /* AI */

#endif /* HASHUNH_H_ */
