/*
 * QLearningETGD.h
 *
 *  Created on: Jun 18, 2014
 *      Author: jandres
 */

#ifndef QLEARNINGETGD_H_
#define QLEARNINGETGD_H_

#include "ReinforcementLearningGD.h"

namespace AI {
namespace Algorithm {
class QLearningETGD : public ReinforcementLearningGD {
 public:
  QLearningETGD(TileCode& tileCode, AI::FLOAT stepSize, AI::FLOAT discountRate,
                AI::FLOAT lambda, Policy::PolicySL& controlPolicy);
};

} /* namespace Algorithm */
} /* namespace AI */

inline AI::Algorithm::QLearningETGD::QLearningETGD(TileCode& tileCode,
                                                   AI::FLOAT stepSize,
                                                   AI::FLOAT discountRate,
                                                   AI::FLOAT lambda,
                                                   Policy::PolicySL& controlPolicy)
    : ReinforcementLearningGD(tileCode, stepSize, discountRate, lambda,
                              controlPolicy) {
}

#endif /* QLEARNINGETGD_H_ */
