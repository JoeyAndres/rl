/*
 * TileCodeMurMur.h
 *
 *  Created on: Jun 15, 2014
 *      Author: jandres
 */

#pragma once

#include "TileCode.h"

namespace rl {
namespace coding {

/*! \class TileCodeMurMur
 *  \brief Tile Code using MurMur3 hash.
 */
class TileCodeMurMur : public TileCode {
 public:
  TileCodeMurMur(vector<DimensionInfo<FLOAT> >& dimensionalInfos, size_t numTilings);
  TileCodeMurMur(vector<DimensionInfo<FLOAT> >& dimensionalInfos, size_t numTilings,
                 size_t sizeHint);
  virtual FEATURE_VECTOR getFeatureVector(const STATE_CONT& parameters) override;
};

} // namespace Coding
} // namespace rl
