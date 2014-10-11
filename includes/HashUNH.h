/*
 * HashUNH.h
 *
 *  Created on: Jun 16, 2014
 *      Author: jandres
 */

#ifndef HASHUNH_H_
#define HASHUNH_H_

#include "GlobalHeader.h"

#include <cstdint>
#include <vector>

#include "HashInterface.h"

using namespace std;

namespace AI {
namespace Algorithm {
namespace Hash{

class UNH : public HashInterface<AI::INT> {
 public:
  virtual AI::INT hash(const AI::BYTE *const byteArray, size_t len);
  virtual AI::INT hash(const vector<AI::BYTE>& byteArray);
};

} /* Hash */
} /* Algorithm */
} /* AI */

#endif /* HASHUNH_H_ */
