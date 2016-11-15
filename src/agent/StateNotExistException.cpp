/*
 * StateNotExistException.cpp
 *
 *  Created on: Jun 13, 2014
 *      Author: jandres
 */

#include "agent/StateNotExistException.h"

namespace rl {
namespace agent {

StateNotExistException::StateNotExistException(string extraMessage) {
  _extraMessage = extraMessage;
}

const char *StateNotExistException::what() const throw() {
  string newMsg = "State does not exist. " + _extraMessage;
  return newMsg.c_str();
}

}  // namespace agent
} /* namespace rl */
