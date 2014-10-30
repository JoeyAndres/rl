/*
 * GradientDescentCC.h
 *
 *  Created on: Jun 15, 2014
 *      Author: jandres
 */

#ifndef GRADIENTDESCENTCC_H_
#define GRADIENTDESCENTCC_H_

#include "GlobalHeader.h"

#include <thread>
#include <cstdint>

#include "threadpool.hpp"
#include "GradientDescent.h"

using namespace boost::threadpool;

namespace AI {
namespace Algorithm {

/*! \class GradientDescentCC
 *  \brief Just an experimental concurrent version of Gradient Descent. This is not recommended to
 *  be utilize yet since Work in Progress.
 */
class GradientDescentCC : public GradientDescent {
 public:
  GradientDescentCC(TileCode& tileCode, AI::FLOAT stepSize,
                    AI::FLOAT discountRate, AI::FLOAT lambda);

 public:
  // Inherited.
  virtual void decreaseEligibilityTraces();
  virtual void backUpWeights(FLOAT tdError);

 protected:
  virtual void _decreaseEligibilityTracesWorker(AI::UINT starti,
                                                AI::UINT length);
  virtual void _backUpWeightsWorker(FLOAT tdError, AI::UINT starti,
                                    AI::UINT length);

 private:
  AI::UINT _maxThreads;
  pool _threadPool;
};

} /* namespace Algorithm */
} /* namespace AI */

inline AI::Algorithm::GradientDescentCC::GradientDescentCC(
    TileCode& tileCode, AI::FLOAT stepSize, AI::FLOAT discountRate,
    AI::FLOAT lambda)
    : GradientDescent(tileCode, stepSize, discountRate, lambda),
      _threadPool(6) {
  _maxThreads = 6;
}

inline void AI::Algorithm::GradientDescentCC::decreaseEligibilityTraces() {
  AI::UINT localIteration = this->getSize() / _maxThreads;
  AI::UINT remainderIteration = this->getSize() % _maxThreads;
  AI::UINT startingi = 0;
  for (AI::UINT i = 0; i < _maxThreads; i++) {
    _threadPool.schedule(
        std::bind(&GradientDescentCC::_decreaseEligibilityTracesWorker, this,
                    startingi, localIteration));
    startingi += localIteration;
  }
  if (remainderIteration > 0) {
    _threadPool.schedule(
        std::bind(&GradientDescentCC::_decreaseEligibilityTracesWorker, this,
                    startingi, remainderIteration));
  }

  _threadPool.wait();
}

inline void AI::Algorithm::GradientDescentCC::backUpWeights(FLOAT tdError) {
  AI::UINT localIteration = this->getSize() / _maxThreads;
  AI::UINT remainderIteration = this->getSize() % _maxThreads;
  AI::UINT startingi = 0;
  for (AI::UINT i = 0; i < _maxThreads; i++) {
    _threadPool.schedule(
        std::bind(&GradientDescentCC::_backUpWeightsWorker, this, tdError,
                    startingi, localIteration));
    startingi += localIteration;
  }
  if (remainderIteration > 0) {
    _threadPool.schedule(
        std::bind(&GradientDescentCC::_backUpWeightsWorker, this, tdError,
                    startingi, remainderIteration));
  }

  _threadPool.wait();
}

inline void AI::Algorithm::GradientDescentCC::_decreaseEligibilityTracesWorker(
    AI::UINT starti, AI::UINT length) {
  AI::FLOAT multiplier = (this->_discountRate) * (this->_lambda);
  for (AI::UINT i = starti; i < starti + length; i++) {
    this->_e.at(i) = multiplier * this->_e.at(i);
  }
}

inline void AI::Algorithm::GradientDescentCC::_backUpWeightsWorker(
    FLOAT tdError, AI::UINT starti, AI::UINT length) {
  AI::FLOAT multiplier = this->_stepSize * tdError;
  for (AI::UINT i = starti; i < starti + length; i++) {
    this->_w[i] += multiplier * this->_e[i];
  }
}

#endif /* GRADIENTDESCENTCC_H_ */
