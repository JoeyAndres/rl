/* 
 * File:   StateActionTransitionException.cpp
 * Author: jandres
 * 
 * Created on June 6, 2014, 4:55 AM
 */

#include "agent/StateActionTransitionException.h"

namespace rl {
namespace agent {
StateActionTransitionException::StateActionTransitionException(
    std::string extraMsg) {
  _extramMsg = extraMsg;
}

const char* StateActionTransitionException::what() const throw () {
  return _extramMsg.c_str();
}

} /* Algorithm */
} /* rl */
