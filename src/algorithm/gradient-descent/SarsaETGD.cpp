//
// Created by jandres on 13/11/16.
//

#include "algorithm/gradient-descent/SarsaETGD.h"

namespace rl {
namespace algorithm {

SarsaETGD::SarsaETGD(
  TileCode& tileCode, rl::FLOAT stepSize, rl::FLOAT discountRate,
  rl::FLOAT lambda, policy::Policy<stateCont, actionCont>& policy)
  : ReinforcementLearningGDET(tileCode, stepSize, discountRate, lambda, policy) {
  this->setLearningPolicy(policy);
}

} /* namespace Algorithm */
} /* namespace rl */
