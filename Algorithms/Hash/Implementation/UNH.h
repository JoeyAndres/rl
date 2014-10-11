/*
 * UNH.h
 *
 *  Created on: Oct 11, 2014
 *      Author: jandres
 */

#include "GlobalHeader.h"

#ifndef ALGORITHMS_HASH_IMPLEMENTATION_UNH_H_
#define ALGORITHMS_HASH_IMPLEMENTATION_UNH_H_

namespace AI {
namespace Algorithm {
namespace Hash{
namespace Implementation{

/**
 * Hash function from University New Hampshire CMAC program.
 * @param coordinates
 * @param num_indices
 * @param memory_size
 * @return
 */
AI::INT hashUNH(AI::INT *coordinates, size_t num_indices, size_t memory_size);

} /* Implementation */
} /* Hash */
} /* Algorithm */
} /* AI */

#endif /* ALGORITHMS_HASH_IMPLEMENTATION_UNH_H_ */
