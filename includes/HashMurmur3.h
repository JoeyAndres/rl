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

#include "HashInterface.h"

using namespace std;

namespace AI {
namespace Algorithm {
namespace Hash {

/**
 * Encapsulates the output of the murmur hash. uint64_t hashVal[2] is
 * the the array being encapsulated since output of murmur3 hash is 128 bit.
 */
struct HashMurmur3Out {
  uint64_t hashVal[2];
};

class Murmur3 : public HashInterface<HashMurmur3Out> {
 public:
  virtual HashMurmur3Out hash(const AI::BYTE *const byteArray, size_t len);
  virtual HashMurmur3Out hash(const vector<AI::BYTE>& byteArray);
};

} /* Hash */
} /* Algorithm */
} /* AI */

#endif /* HASH_H_ */
