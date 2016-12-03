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

#include <random>
#include <vector>

#include "TileCode.h"

using std::vector;

namespace rl {
namespace coding {

/*! \class TileCodeMurMur
 *  \brief Tile Code using MurMur3 hash.
 */
class TileCodeMurMur : public TileCode {
 public:
  TileCodeMurMur(const vector<DimensionInfo<FLOAT>>& dimensionalInfos,
                 size_t numTilings);
  TileCodeMurMur(const vector<DimensionInfo<FLOAT>>& dimensionalInfos,
                 size_t numTilings,
                 size_t sizeHint);
  FEATURE_VECTOR getFeatureVector(const floatVector& parameters) override;
};

}  // namespace coding
}  // namespace rl
