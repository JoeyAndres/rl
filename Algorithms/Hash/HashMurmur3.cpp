/*
 * Hash.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: jandres
 */

#include "GlobalHeader.h"

#include <iostream>

#include "HashMurmur3.h"
#include "MurmurHash3.h"

using namespace std;

void AI::getHashVal(const vector<AI::INT>& key, HashMurmur3Out& out) {
	MurmurHash3_x64_128(&key[0], key.size() * sizeof(AI::INT),
			AI::MURMUR_HASH_SEED, &(out.hashVal[0]));
}
