/*
 * SuperFastHash.h
 *
 *  Created on: Oct 10, 2014
 *      Author: jandres
 */

#include <cstdint>

#ifndef ALGORITHMS_HASH_HASHIMPLEMENTATION_SUPERFASTHASH_H_
#define ALGORITHMS_HASH_HASHIMPLEMENTATION_SUPERFASTHASH_H_

namespace AI {
namespace Algorithm {
namespace Hash {
namespace Implementation {
uint32_t SuperFastHash(const char * data, int len);
} /* Implementation */
} /* Hash */
} /* Algorithm */
} /* AI */

#endif /* ALGORITHMS_HASH_HASHIMPLEMENTATION_SUPERFASTHASH_H_ */
