/*
 * MountainCarEnvironment.h
 *
 *  Created on: Jun 12, 2014
 *      Author: jandres
 */

#ifndef MOUNTAINCARENVIRONMENT_H_
#define MOUNTAINCARENVIRONMENT_H_

#include "GlobalHeader.h"

#include <vector>

using namespace std;

#define POS 0
#define VEL 1

namespace AI {

  class MountainCarEnvironment {
  private:
	MountainCarEnvironment();
  public:
	static MountainCarEnvironment& getInstance();

	void reset();

	AI::FLOAT applyAction(AI::INT Action);
	const vector<AI::FLOAT>& getCurrentState() const;
  private:
	vector<AI::FLOAT> _currentState;
  public:
	AI::FLOAT _currentReward;
  };

} /* namespace AI */

#endif /* MOUNTAINCARENVIRONMENT_H_ */
