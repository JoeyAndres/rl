/*
 * HashSuperFastHash.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: jandres
 */

#include "HashSuperFastHash.h"

#include "SuperFastHash.h"

namespace AI {
namespace Algorithm {
namespace Hash {

AI::INT SuperFastHash::hash(const AI::BYTE * const byteArray, size_t len) {
  return Implementation::SuperFastHash((char*) byteArray, len);
}

AI::INT SuperFastHash::hash(const vector<AI::BYTE>& msg) {
  return Implementation::SuperFastHash((char*) msg.data(),
                                       msg.size() * sizeof(AI::BYTE));
}

} /* Hash */
} /* Algorithm */
} /* AI */
