/*
 * UNH.h
 *
 *  Created on: Oct 11, 2014
 *      Author: jandres
 */
#pragma once

#include <cstdint>

/**
 * Hash function from University New Hampshire CMAC program.
 * @param coordinates
 * @param num_indices
 * @param memory_size
 * @return
 */
extern int64_t hashUNH(int64_t *coordinates, size_t num_indices, size_t memory_size);
