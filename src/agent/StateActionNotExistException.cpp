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

#include "agent/StateActionNotExistException.h"

namespace rl {
namespace agent {

StateActionNotExistException::StateActionNotExistException(
  string extraMessage) {
  _extraMessage = extraMessage;
}

const char *StateActionNotExistException::what() const throw() {
  string concatenateExtraMessage = "StateAction pair does not exist."
    + _extraMessage;
  return concatenateExtraMessage.c_str();
}

}  // namespace agent
}  // namespace rl
