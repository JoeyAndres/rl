/*
 * Hash.h
 *
 *  Created on: Jun 15, 2014
 *      Author: jandres
 */

#ifndef HASH_H_
#define HASH_H_

#include "GlobalHeader.h"

#include <cstdint>
#include <vector>

using namespace std;

namespace AI {
namespace Algorithm {
/**
 * Encapsulates the output of the murmur hash. uint64_t hashVal[2] is
 * the the array being encapsulated since output of murmur3 hash is 128 bit.
 */
struct HashMurmur3Out {
	uint64_t hashVal[2];
};

void getHashVal(const vector<AI::INT>& key, HashMurmur3Out& out);

} /* Algorithm */
} /* AI */

#endif /* HASH_H_ */
