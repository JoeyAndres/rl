/*
 * StateActionNotExist.h
 *
 *  Created on: Jun 13, 2014
 *      Author: jandres
 */

#ifndef STATEACTIONNOTEXISTEXCEPTION_H_
#define STATEACTIONNOTEXISTEXCEPTION_H_

#include <exception>
#include <string>

using namespace std;

namespace AI {
/**
 * StateActionNotExistException
 * Handling situations when StateAction being queried
 * does not exist. e.g. map[StateAction] throws out of
 * range since StateAction does not exist.
 */
class StateActionNotExistException : public exception {
 public:
  /**
   * @param extraMessage To add more details of the cause
   * of exception. This should put the exception in a better context.
   */
  StateActionNotExistException(string extraMessage);
  virtual const char* what() const throw ();

 private:
  string _extraMessage;
};

} /* namespace AI */

#endif /* STATEACTIONNOTEXISTEXCEPTION_H_ */
