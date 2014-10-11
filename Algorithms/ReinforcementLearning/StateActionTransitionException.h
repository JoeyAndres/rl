/* 
 * File:   StateActionTransitionException.h
 * Author: jandres
 *
 * Created on June 6, 2014, 4:55 AM
 */

#ifndef STATEACTIONTRANSITIONEXCEPTION_H
#define	STATEACTIONTRANSITIONEXCEPTION_H

#include <exception>
#include <string>

namespace AI {

class StateActionTransitionException : public std::exception {
 public:
  StateActionTransitionException(std::string extraMsg);

  virtual const char* what() const throw ();

 private:
  std::string _extramMsg;
};
}

#endif	/* STATEACTIONTRANSITIONEXCEPTION_H */

