/* 
 * File:   SarsaETGD.h
 * Author: jandres
 *
 * Created on June 10, 2014, 5:06 AM
 */

#ifndef SARSAETGD_H
#define	SARSAETGD_H

#include "GlobalHeader.h"

#include <vector>
#include <map>

#include "GradientDescent.h"
#include "StateAction.h"
#include "ReinforcementLearningGD.h"

using namespace std;

namespace AI {
namespace Algorithm {
namespace SL {

/*! \class SarsaETGD
 *  \brief Gradient Descent with Sarsa implementation (the same policy for
 *         learning and action selection).
 */
class SarsaETGD final: public ReinforcementLearningGD {
 public:
  SarsaETGD(TileCode& tileCode, AI::FLOAT stepSize,
            AI::FLOAT discountRate,
            AI::FLOAT lambda,
            Policy::Policy<vector<FLOAT>, vector<FLOAT> >& policy);
};

SarsaETGD::SarsaETGD(
    TileCode& tileCode, AI::FLOAT stepSize, AI::FLOAT discountRate,
    AI::FLOAT lambda, Policy::Policy<vector<FLOAT>, vector<FLOAT> >& policy)
    : ReinforcementLearningGD(tileCode, stepSize, discountRate, lambda, policy) {
  this->setLearningPolicy(policy);
}

} // namespace SL
} /* namespace Algorithm */
} /* namespace AI */

#endif	/* SARSAETGD_H */

