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

namespace rl {
namespace hash {

/*! \class SuperFastHash
 *  \brief SuperFastHash implementation encapsulated.
 */
class SuperFastHash : public HashInterface<rl::INT> {
 public:
  virtual rl::INT hash(const rl::BYTE * const byteArray, size_t len);
  virtual rl::INT hash(const vector<rl::BYTE>& byteArray);
};

} /* Hash */
} /* rl */

#endif /* HASHSUPERFASTHASH_H_ */
