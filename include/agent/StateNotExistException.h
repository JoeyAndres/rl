/*
 * StateNotExistException.h
 *
 *  Created on: Jun 13, 2014
 *      Author: jandres
 */

#ifndef STATENOTEXISTEXCEPTION_H_
#define STATENOTEXISTEXCEPTION_H_

#include <exception>
#include <string>

using namespace std;

namespace rl {
namespace agent {

/*! \StateNotExistException
 *  \brief exception when State does not exist.
 */
class StateNotExistException : exception {
 public:
  StateNotExistException(string extraMessage);
  virtual const char *what() const throw();
 private:
  string _extraMessage;
};

}  // namespace agent
}  // namespace rl

#endif /* STATENOTEXISTEXCEPTION_H_ */
