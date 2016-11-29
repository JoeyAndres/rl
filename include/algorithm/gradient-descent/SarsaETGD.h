/* 
 * File:   SarsaETGD.h
 * Author: jandres
 *
 * Created on June 10, 2014, 5:06 AM
 */

#ifndef SARSAETGD_H
#define	SARSAETGD_H

#include "../../declares.h"

#include <vector>
#include <map>

#include "GradientDescent.h"
#include "../../agent/StateAction.h"
#include "ReinforcementLearningGDET.h"

using namespace std;

namespace rl {
namespace algorithm {

using namespace coding;

/*! \class SarsaETGD
 *  \brief Gradient Descent with Sarsa implementation (the same policy for
 *         learning and action selection).
 */
class SarsaETGD final: public ReinforcementLearningGDET {
 public:
  SarsaETGD(TileCode& tileCode, rl::FLOAT stepSize,
            rl::FLOAT discountRate,
            rl::FLOAT lambda,
            policy::Policy<vector<FLOAT>, vector<FLOAT> >& policy);
};

} /* namespace algorithm */
} /* namespace rl */

#endif	/* SARSAETGD_H */

