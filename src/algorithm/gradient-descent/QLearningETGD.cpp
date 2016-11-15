//
// Created by jandres on 13/11/16.
//

#include "algorithm/gradient-descent/QLearningETGD.h"

namespace rl {
namespace algorithm {

QLearningETGD::QLearningETGD(
  TileCode& tileCode, rl::FLOAT stepSize, rl::FLOAT discountRate,
  rl::FLOAT lambda, policy::PolicySL& controlPolicy)
  : ReinforcementLearningGD(tileCode, stepSize, discountRate, lambda,
                            controlPolicy) {
}

} /* namespace Algorithm */
} /* namespace rl */
