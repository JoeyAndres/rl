/*
 * Hash.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: jandres
 */

#include "declares.h"

#include <iostream>

#include "HashMurmur3.h"
#include "MurmurHash3.h"

using namespace std;

namespace AI{
namespace Algorithm{
namespace Hash{

HashMurmur3Out Murmur3::hash(const AI::BYTE *const byteArray,
                                                  size_t len) {
  HashMurmur3Out out;
  Implementation::MurmurHash3_x64_128(&byteArray[0], len * sizeof(AI::BYTE),
                      AI::MURMUR_HASH_SEED, &(out.hashVal[0]));
  return out;
}

HashMurmur3Out Murmur3::hash(const vector<AI::BYTE>& msg) {
  HashMurmur3Out out;
  Implementation::MurmurHash3_x64_128(&msg[0], msg.size() * sizeof(AI::BYTE),
                      AI::MURMUR_HASH_SEED, &(out.hashVal[0]));
  return out;
}

} /* Hash */
} /* Algorithm */
} /* AI */
