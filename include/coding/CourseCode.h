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

#include <array>
#include <memory>

#include "../declares.h"

using std::array;
using std::shared_ptr;

namespace rl {
namespace coding {

/*!\class CourseCode
 * \brief Abstract class for course coding.
 * \tparam D Number of dimension.
 */
template <size_t D>
class CourseCode {
 public:
  /**
   * No-arg constructor.
   */
  CourseCode();

  /**
   * @return number of dimension.
   */
  virtual size_t getDimension() const;

  /**
   * Get the value of the parameters in the real space.
   * @param parameters
   * @return corresponding value.
   */
  virtual FLOAT getValueFromParameters(
    const floatArray<D>& parameters) const = 0;

  /**
   * @return size of the weight vector.
   */
  virtual size_t getSize() const = 0;
};

/*!\typedef spCourseCode
 * \brief Wraps CourseCode
 * \tparam D Number of dimension.
 */
template <size_t D>
using spCourseCode = shared_ptr<CourseCode<D>>;

template <size_t D>
CourseCode<D>::CourseCode() {
}

template <size_t D>
size_t CourseCode<D>::getDimension() const {
  return D;
}

}  // namespace coding
}  // namespace rl
