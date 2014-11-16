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
namespace SL {

/*! \class QLearningETGD
 *  \brief Gradient Descent with QLearning implementation (Separate control
 *         and learning policy).
 */
class QLearningETGD : public ReinforcementLearningGD {
 public:
  QLearningETGD(TileCode& tileCode, AI::FLOAT stepSize, AI::FLOAT discountRate,
                AI::FLOAT lambda, Policy::PolicySL& controlPolicy);
};

inline QLearningETGD::QLearningETGD(
    TileCode& tileCode, AI::FLOAT stepSize, AI::FLOAT discountRate,
    AI::FLOAT lambda, Policy::PolicySL& controlPolicy)
    : ReinforcementLearningGD(tileCode, stepSize, discountRate, lambda,
                              controlPolicy) {
}

} // namespace SL
} /* namespace Algorithm */
} /* namespace AI */

#endif /* QLEARNINGETGD_H_ */
