/**
 * HashUNH.cpp
 */

#include <random>

#include "HashUNH.h"

namespace AI {
  /**
   * Hash function from University New Hampshire CMAC program.
   * @param coordinates
   * @param num_indices
   * @param memory_size
   * @return
   */
  AI::INT hashUNH(AI::INT *coordinates, size_t num_indices, size_t memory_size) {
	static AI::INT first_call = 1;
	static AI::INT rndseq[2048];
	size_t i, k;
	AI::INT index;
	AI::INT sum = 0;

	std::default_random_engine randomEngine;

	/* if first call to hashing, initialize table of random numbers */
	if (first_call) {
	  for (k = 0; k < 2048; k++) {
		rndseq[k] = 0;
		for (i = 0; i < sizeof(AI::INT); ++i)
		  rndseq[k] = (rndseq[k] << 8) | (randomEngine() & 0xff);
	  }
	  first_call = 0;
	}

	for (i = 0; i < num_indices; i++) {
	  /* add random table offset for this dimension and wrap around */
	  index = coordinates[i];
	  index += (449 * i);
	  index %= 2048;
	  while (index < 0)
		index += 2048;

	  /* add selected random number to sum */
	  sum += (AI::INT) rndseq[(AI::INT) index];
	}
	index = (AI::INT) (sum % memory_size);
	while (index < 0)
	  index += memory_size;

	return (index);
  }

  AI::INT hashUNH(vector<AI::INT>& coordinateVector, size_t memorySize) {
	return hashUNH(&coordinateVector[0], coordinateVector.size(), memorySize);
  }
}
