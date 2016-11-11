/*
 * utility.h
 *
 *  Created on: Oct 8, 2014
 *      Author: jandres
 */

#ifndef ALGORITHMS_UTILITY_H_
#define ALGORITHMS_UTILITY_H_

#include <map>

/**
 * For measuring duration of a program block.
 */
#define BEGIN_TIME_TEST() std::chrono::time_point<std::chrono::system_clock> start, end; \
  start = std::chrono::system_clock::now();

#define END_TIME_TEST() end = std::chrono::system_clock::now();         \
  std::chrono::duration<double> elapsed_seconds = end-start;            \
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);     \
  std::cout << "Program runtime Info: " << std::ctime(&end_time)        \
  << "elapsed time: " << elapsed_seconds.count() << "s\n" << endl;

namespace AI {
namespace Utility {

/**
 * @see http://stackoverflow.com/a/5056797
 * @param src
 * @return
 */
template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p) {
  return std::pair<B,A>(p.second, p.first);
}

/**
 * Flips an associative container of A,B pairs to B,A pairs
 * @see http://stackoverflow.com/a/5056797
 * @param src
 * @return
 */
template<typename A, typename B, template<class,class,class...> class M, class... Args>
std::multimap<B,A> flipMap(const M<A,B,Args...> &src) {
  std::multimap<B,A> dst;
  std::transform(src.begin(), src.end(),
                 std::inserter(dst, dst.begin()),
                 flip_pair<A,B>);
  return dst;
}
} /* namespace Utility */
} /* namespace AI */

#endif /* ALGORITHMS_UTILITY_H_ */
