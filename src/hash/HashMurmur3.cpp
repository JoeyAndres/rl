/*
 * Hash.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: jandres
 */

#include "declares.h"

#include <iostream>

#include "hash/HashMurmur3.h"
#include "murmur3/MurmurHash3.h"

using namespace std;

namespace rl{
namespace hash{

HashMurmur3Out Murmur3::hash(const rl::BYTE *const byteArray,
                                                  size_t len) {
  HashMurmur3Out out;
  MurmurHash3_x64_128(&byteArray[0], len * sizeof(rl::BYTE),
                      rl::MURMUR_HASH_SEED, &(out.hashVal[0]));
  return out;
}

HashMurmur3Out Murmur3::hash(const vector<rl::BYTE>& msg) {
  HashMurmur3Out out;
  MurmurHash3_x64_128(&msg[0], msg.size() * sizeof(rl::BYTE),
                      rl::MURMUR_HASH_SEED, &(out.hashVal[0]));
  return out;
}

} /* Hash */
} /* rl */
