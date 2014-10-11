/**
 * HashUNH.cpp
 */

#include "HashUNH.h"
#include "UNH.h"

namespace AI {
namespace Algorithm {
namespace Hash {

AI::INT Hash::UNH::hash(const AI::BYTE * const byteArray, size_t len) {
  return Implementation::hashUNH((AI::INT*) byteArray, len * sizeof(AI::INT),
                                 4096);
}

AI::INT Hash::UNH::hash(const vector<AI::BYTE>& msg) {
  return Implementation::hashUNH((AI::INT*) msg.data(),
                                 msg.size() * sizeof(AI::INT), 4096);
}

} /* Hash */
} /* Algorithm */
} /* AI */
