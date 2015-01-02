/* 
 * File:   globalHeader.h
 * Author: Joey Andres
 *
 * Created on June 3, 2014, 4:45 PM
 */

#ifndef GLOBALHEADER_H
#define	GLOBALHEADER_H

#include <cstdint>
#include <vector>

#define DEBUG
//#define TEST_PRINT
//#define TEST_TILE_CODING

#ifndef DEBUG
#define NDEBUG  // Gets rid of assertions.
#endif

namespace AI {
  typedef double FLOAT;  //!< Default floating type.
  typedef uint64_t UINT;  //!< Default unsigned integer type.
  typedef int64_t INT;  //!< Default signed integer type.
  typedef uint8_t BYTE;  //!< Byte type.

  const FLOAT DEFAULT_GREEDINESS_LEARNING_POLICY = 1.0F;

  // Hashing constants.
  const UINT MURMUR_HASH_SEED = 0x666;

  const UINT MAX_EPISODES = 100000;

  typedef std::vector<FLOAT> STATE_CONT;  //!< State container.
  typedef std::vector<FLOAT> ACTION_CONT;  //!< Action container.

  /*! \typedef FEATURE_VECTOR
   *  Feature vector is a data structure for Tile Coding. It is the indices
   *  that contains the data points to be sampled.
   */
  typedef std::vector<UINT> FEATURE_VECTOR;
}

#endif	/* GLOBALHEADER_H */

