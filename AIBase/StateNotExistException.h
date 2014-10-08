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

namespace AI {

class StateNotExistException: exception {
public:
	StateNotExistException(string extraMessage);
	virtual const char* what() const throw ();
private:
	string _extraMessage;
};

} /* namespace AI */

#endif /* STATENOTEXISTEXCEPTION_H_ */
