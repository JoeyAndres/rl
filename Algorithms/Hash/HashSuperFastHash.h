/*
 * HashSuperFastHash.h
 *
 *  Created on: Jun 18, 2014
 *      Author: jandres
 */

#ifndef HASHSUPERFASTHASH_H_
#define HASHSUPERFASTHASH_H_

#include <cstdint>

#include "HashInterface.h"

namespace AI {
namespace Algorithm {
namespace Hash {

class SuperFastHash : public HashInterface<AI::INT> {
 public:
  virtual AI::INT hash(const AI::BYTE *const byteArray, size_t len);
  virtual AI::INT hash(const vector<AI::BYTE>& byteArray);
};

} /* Hash */
} /* Algorithm */
} /* AI */

#endif /* HASHSUPERFASTHASH_H_ */
