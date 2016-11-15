/*
 * HashSuperFastHash.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: jandres
 */

#include "hash/HashSuperFastHash.h"
#include "superfasthash/SuperFastHash.h"

namespace rl {
namespace hash {

rl::INT SuperFastHash::hash(const rl::BYTE * const byteArray, size_t len) {
  return ::SuperFastHash((char*) byteArray, len);
}

rl::INT SuperFastHash::hash(const vector<rl::BYTE>& msg) {
  return ::SuperFastHash((char*) msg.data(),
                         msg.size() * sizeof(rl::BYTE));
}

} /* Hash */
} /* rl */
