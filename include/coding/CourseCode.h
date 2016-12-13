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

namespace rl {
namespace coding {

/*!\class CourseCode
 * \brief Abstract class for course coding.
 * \tparam D Number of dimension.
 */
template <size_t D>
class CourseCode {
 public:
  virtual FEATURE_VECTOR getFeatureVector(const floatArray<D>& parameters) = 0;
  virtual size_t getSize() const = 0;
  virtual size_t getDimension() const;
};

}  // namespace coding
}  // namespace rl
