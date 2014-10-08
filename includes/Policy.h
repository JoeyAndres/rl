/* 
 * File:   Policy.h
 * Author: jandres
 *
 * Created on June 6, 2014, 5:48 PM
 */

#ifndef POLICY_H
#define	POLICY_H

#include "GlobalHeader.h"

#include <map>
#include <vector>

#include "StateAction.h"

using namespace std;

namespace AI {
namespace Algorithm {

template<class S, class A>
class Policy {
public:
	virtual const A& getAction(const map<A, AI::FLOAT>& actionValues,
			const set<A>& actionSet) = 0;
private:

};

typedef Policy<vector<AI::FLOAT>, vector<AI::FLOAT> > PolicySL;
}
}

#endif	/* POLICY_H */

