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

#include <cassandra.h>
#include <string>
#include <memory>
#include <tuple>
#include <exception>
#include <vector>

#include "../declares.h"
#include "../utility/CRUDInterface.h"
#include "TileCodeContainerSegment.h"

using std::string;
using std::shared_ptr;
using std::tuple;
using std::exception;
using std::vector;

namespace rl {
namespace coding {

class TileCodeContainer;
using spTileCodeContainer = shared_ptr<TileCodeContainer>;

class TileCodeContainer :
  public utility::CRUDInterface,
  public utility::IndexAccessorInterface<TileCodeContainerCell> {
 public:
  TileCodeContainer(size_t size, FLOAT initialValue);
  TileCodeContainer(const string& id);

  void create() override;
  void read() override;
  void update() override;
  void delete2() override;

  string getID() const;
  size_t getSegmentCount() const;

  std::vector<spTileCodeContainerSegment> getSegments() const;

  TileCodeContainerCell& at(size_t i) override;

 protected:
  void _setInserted(bool inserted);
  void _deleteAllSegments();

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
  static void _createTileContainerTable();

  static string _insertTileCodeContainer(size_t size, FLOAT initialValue);

  static tuple<string, size_t, FLOAT>  _getTileContainer(string uuid)
  throw(exception);

 protected:
  size_t _size;
  FLOAT _initialValue = 0.0F;
  string _id = "";
  bool _inserted = false;
  vector<spTileCodeContainerSegment> _segments;
};

}  // namespace coding
}  // namespace rl
