/*
 * StateActionNotExist.cpp
 *
 *  Created on: Jun 13, 2014
 *      Author: jandres
 */

#include "agent/StateActionNotExistException.h"

rl::agent::StateActionNotExistException::StateActionNotExistException(
    string extraMessage) {
  _extraMessage = extraMessage;
}

const char* rl::agent::StateActionNotExistException::what() const throw () {
  string concatenateExtraMessage = "StateAction pair does not exist."
      + _extraMessage;
  return concatenateExtraMessage.c_str();
}
