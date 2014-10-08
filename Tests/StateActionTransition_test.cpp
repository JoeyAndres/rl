#include <vector>
#include <iostream>

#include "UnitTest++.h"
#include "StateActionTransition.h"
#include "StateActionTransitionException.h"

using std::vector;

using namespace AI;
using namespace std;

TEST(StateActionTransitionInitialization) {
	StateActionTransition<AI::INT> sat(1.0F, 0.2F);

	CHECK(sat.getSize() == 0);
}

TEST(StateActionTransitionUpdate) {
	StateActionTransition<AI::INT> sat(1.0F, 0.2F);
	AI::INT state01(1);
	sat.update(state01, 10);
	CHECK(sat.getSize() == 1);
	CHECK(sat.getNextState() == state01);

	AI::INT state02(2);
	sat.update(state02, 10);
	sat.update(state02, 10);
	CHECK(sat.getSize() == 2);

	AI::INT state03(3);
	sat.update(state03, 10);
	sat.update(state03, 10);
	sat.update(state03, 10);
	CHECK(sat.getSize() == 3);

	AI::UINT state01OccurenceCount, state02OccurenceCount,
			state03OccurenceCount;
	state01OccurenceCount = state02OccurenceCount = state03OccurenceCount = 0;
	for (AI::UINT i = 0; i < 1000; i++) {
		const AI::INT& state = sat.getNextState();
		if (state == state01) {
			state01OccurenceCount++;
		} else if (state == state02) {
			state02OccurenceCount++;
		} else if (state == state03) {
			state03OccurenceCount++;
		} else {
			CHECK(false);
		}
	}

	cout << "State01 occurence count: " << state01OccurenceCount << endl;
	cout << "State02 occurence count: " << state02OccurenceCount << endl;
	cout << "State03 occurence count: " << state03OccurenceCount << endl;
	CHECK(state01OccurenceCount < state02OccurenceCount);
	CHECK(state02OccurenceCount < state03OccurenceCount);

	// Change environment.
	sat.update(state02, 10);
	sat.update(state02, 10);
	sat.update(state02, 10);
	sat.update(state02, 10);

	state01OccurenceCount = state02OccurenceCount = state03OccurenceCount = 0;
	for (AI::UINT i = 0; i < 1000; i++) {
		const AI::INT& state = sat.getNextState();
		if (state == state01) {
			state01OccurenceCount++;
		} else if (state == state02) {
			state02OccurenceCount++;
		} else if (state == state03) {
			state03OccurenceCount++;
		} else {
			CHECK(false);
		}
	}

	cout << endl << "Environment Changed" << endl;
	cout << "State01 occurence count: " << state01OccurenceCount << endl;
	cout << "State02 occurence count: " << state02OccurenceCount << endl;
	cout << "State03 occurence count: " << state03OccurenceCount << endl;
	CHECK(state01OccurenceCount < state02OccurenceCount);
	CHECK(state03OccurenceCount < state02OccurenceCount);
}

TEST(StateActionTransitionExceptionCatching) {
	StateActionTransition<AI::INT> sat(1.0F, 0.2F);
	try {
		sat.getReward(AI::INT(23));
	} catch (StateActionTransitionException& exception) {
		cout << exception.what() << endl;
	}

	try {
		sat.getNextState();
	} catch (StateActionTransitionException& exception) {
		cout << exception.what() << endl;
	}

	sat.update(10, 100);

	try {
		sat.getReward(23);
	} catch (StateActionTransitionException& exception) {
		cout << exception.what() << endl;
	}
}

int main(void) {
	return UnitTest::RunAllTests();
}
