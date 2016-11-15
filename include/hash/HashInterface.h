/*
 * HashBase.h
 *
 *  Created on: Oct 10, 2014
 *      Author: jandres
 */

#ifndef ALGORITHMS_HASH_HASHINTERFACE_H_
#define ALGORITHMS_HASH_HASHINTERFACE_H_

#include <cstdlib>
#include <cstdint>
#include <vector>

#include "../declares.h"

using std::vector;

namespace rl {
namespace hash {

/*! \class HashInterface
 *  \brief Interface for all hash encapsulation.
 *  \tparam RET return data type.
 */
template<class RET>
class HashInterface {
 public:
  /**
   * @param byteArray
   * @param len
   * @return h(byteArray)
   */
  virtual RET hash(const rl::BYTE * const byteArray, size_t len) = 0;
  virtual RET hash(const vector<rl::BYTE>& byteArray) = 0;
};

} /* namespace Hash */
} /* namespace rl */

#endif /* ALGORITHMS_HASH_HASHINTERFACE_H_ */
