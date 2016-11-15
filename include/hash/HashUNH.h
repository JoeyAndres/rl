/*
 * HashUNH.h
 *
 *  Created on: Jun 16, 2014
 *      Author: jandres
 */

#ifndef HASHUNH_H_
#define HASHUNH_H_

#include "../declares.h"

#include <cstdint>
#include <vector>

#include "HashInterface.h"

using namespace std;

namespace rl {
namespace hash {

/*! \class UNH
 *  \brief UNH implementation encapsulation.
 */
class UNH : public HashInterface<rl::INT> {
 public:
  virtual rl::INT hash(const rl::BYTE * const byteArray, size_t len);
  virtual rl::INT hash(const vector<rl::BYTE>& byteArray);
};

} /* Hash */
} /* rl */

#endif /* HASHUNH_H_ */
