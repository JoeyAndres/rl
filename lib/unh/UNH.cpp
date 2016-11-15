/*
 * UNH.cpp
 *
 *  Created on: Oct 11, 2014
 *      Author: jandres
 */

#include <random>

#include "UNH.h"

rl::INT hashUNH(rl::INT *coordinates, size_t num_indices, size_t memory_size) {
  static rl::INT first_call = 1;
  static rl::INT rndseq[2048];
  size_t i, k;
  rl::INT index;
  rl::INT sum = 0;

  std::default_random_engine randomEngine;

  /* if first call to hashing, initialize table of random numbers */
  if (first_call) {
    for (k = 0; k < 2048; k++) {
      rndseq[k] = 0;
      for (i = 0; i < sizeof(rl::INT); ++i)
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
    sum += (rl::INT) rndseq[(rl::INT) index];
  }
  index = (rl::INT) (sum % memory_size);
  while (index < 0)
    index += memory_size;

  return (index);
}
