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

namespace rl {
namespace agent {

/*! \class StateActionTransitionException
 *  \brief exception when StateActionTransition does not exist.
 */
class StateActionTransitionException : public std::exception {
 public:
  StateActionTransitionException(std::string extraMsg);

  virtual const char* what() const throw ();

 private:
  std::string _extramMsg;
};

}  // namespace agent
}  /* rl */

#endif	/* STATEACTIONTRANSITIONEXCEPTION_H */

