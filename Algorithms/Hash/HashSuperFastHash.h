/*
 * HashSuperFastHash.h
 *
 *  Created on: Jun 18, 2014
 *      Author: jandres
 */

#ifndef HASHSUPERFASTHASH_H_
#define HASHSUPERFASTHASH_H_

#include "stdint.h" /* Replace with <stdint.h> if appropriate */

namespace AI {
uint32_t SuperFastHash(const char * data, int len);
}

#endif /* HASHSUPERFASTHASH_H_ */
