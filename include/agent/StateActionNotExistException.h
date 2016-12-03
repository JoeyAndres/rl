/**
 * rl - Reinforcement Learning
 * Copyright (C) 2016  Joey Andres<yeojserdna@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <exception>
#include <string>

using std::string;

namespace rl {
namespace agent {

/*! \class StateActionNotExistException
 *  \brief Handling situation when StateAction being queried does not exist.
 *
 * Handling situations when StateAction being query does not exist.
 * e.g. map[StateAction] throws out of range since StateAction does not exist.
 */
class StateActionNotExistException : public std::exception {
 public:
  /**
   * @param extraMessage To add more details of the cause
   * of exception. This should put the exception in a better context.
   */
  explicit StateActionNotExistException(string extraMessage);
  virtual const char *what() const throw();

 private:
  string _extraMessage;
};

}  // namespace agent
}  // namespace rl
