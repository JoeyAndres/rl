/*
 * utility.h
 *
 *  Created on: Oct 8, 2014
 *      Author: jandres
 */

#ifndef ALGORITHMS_UTILITY_H_
#define ALGORITHMS_UTILITY_H_

/**
 * For measuring duration of a program block.
 */
#define BEGIN_TIME_TEST() std::chrono::time_point<std::chrono::system_clock> start, end;\
													start = std::chrono::system_clock::now();

#define END_TIME_TEST() end = std::chrono::system_clock::now();\
std::chrono::duration<double> elapsed_seconds = end-start;\
std::time_t end_time = std::chrono::system_clock::to_time_t(end);\
std::cout << "Program runtime Info: " << std::ctime(&end_time)\
	    << "elapsed time: " << elapsed_seconds.count() << "s\n" << endl;

#endif /* ALGORITHMS_UTILITY_H_ */
