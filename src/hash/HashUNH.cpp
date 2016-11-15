/**
 * HashUNH.cpp
 */

#include "hash/HashUNH.h"
#include "unh/UNH.h"

namespace rl {
namespace hash {

INT UNH::hash(const rl::BYTE * const byteArray, size_t len) {
  return hashUNH((rl::INT*) byteArray, len * sizeof(rl::INT), 4096);
}

INT UNH::hash(const vector<rl::BYTE>& msg) {
  return hashUNH((rl::INT*) msg.data(), msg.size() * sizeof(rl::INT), 4096);
}

} /* Hash */
} /* rl */
