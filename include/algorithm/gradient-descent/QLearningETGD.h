/*
 * QLearningETGD.h
 *
 *  Created on: Jun 18, 2014
 *      Author: jandres
 */

#ifndef QLEARNINGETGD_H_
#define QLEARNINGETGD_H_

#include "ReinforcementLearningGD.h"

namespace rl {
namespace algorithm {

using namespace coding;

/*! \class QLearningETGD
 *  \brief Gradient Descent with QLearning implementation (Separate control
 *         and learning policy).
 */
class QLearningETGD : public ReinforcementLearningGD {
 public:
  QLearningETGD(TileCode& tileCode, rl::FLOAT stepSize, rl::FLOAT discountRate,
                rl::FLOAT lambda, policy::PolicySL& controlPolicy);
};

} /* namespace algorithm */
} /* namespace rl */

#endif /* QLEARNINGETGD_H_ */
