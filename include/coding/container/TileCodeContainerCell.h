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

#ifdef ENABLE_DB

#include <cassandra.h>
#include <string>
#include <memory>

#include "../../declares.h"

using std::string;
using std::shared_ptr;

namespace rl {
namespace coding {

/*!\class TileCodeContainerCell
 * \brief Represents a single data that can be modified or retrieved.
 */
class TileCodeContainerCell {
 public:
  /**
   * @param tileCodeContainerId ID of the parent TileCodeContainer.
   * @param segmentIndex Index of this segment.
   * @param index Index of the data within segment.
   */
  TileCodeContainerCell(string tileCodeContainerId,
                        size_t segmentIndex,
                        size_t index);

  /**
   * @return the data being represented in this cell.
   */
  FLOAT get() const;

  /**
   * @param val The value to set this cell.
   */
  void set(FLOAT val);

  // operator overload.
  TileCodeContainerCell& operator=(FLOAT val);
  TileCodeContainerCell& operator+=(FLOAT val);

  // Implicit conversion to FLOAT.
  operator FLOAT() const;

 protected:
  string _tileCodeContainerId;
  size_t _segmentIndex;
  size_t _index;
};

using spTileCodeContainerCell = shared_ptr<TileCodeContainerCell>;

}  // namespace coding
}  // namespace rl

#endif  // #ifdef ENABLE_DB
