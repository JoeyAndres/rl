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

#include <string>
#include <vector>
#include <memory>

#include "../declares.h"
#include "../utility/CRUDInterface.h"
#include "../utility/IndexAccessorInterface.h"
#include "TileCodeContainerCell.h"

using std::string;
using std::vector;
using std::shared_ptr;

namespace rl {
namespace coding {

class TileCodeContainerSegment :
  public utility::CRUDInterface,
  public utility::IndexAccessorInterface<TileCodeContainerCell> {
 public:
  TileCodeContainerSegment(
    const string& tileCodeContainerId,
    size_t size,
    size_t index);
  TileCodeContainerSegment(
    const string& tileCodeContainer,
    size_t index);

  void create() override;
  void read() override;
  void update() override;
  void delete2() override;

  TileCodeContainerCell& at(size_t i) override;
  TileCodeContainerCell at(size_t i) const override;

 public:
  /**
   * Initialize the underlying database for TileCodeContainer.
   */
  static void createSchema();

  /**
   * Destroys the underlying database for TileCodeContainer.
   */
  static void destroySchema();

 protected:
  string _tileCodeContainerId;
  size_t _size;
  size_t _segmentIndex;
  vector<FLOAT> _data;  // TODO(jandres): Remove this.
  vector<TileCodeContainerCell> _data2;
};

using spTileCodeContainerSegment = shared_ptr<TileCodeContainerSegment>;

}  // namespace coding
}  // namespace rl
