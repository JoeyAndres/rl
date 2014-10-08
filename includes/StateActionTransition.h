/* 
 * File:   StateActionTransition.h
 * Author: jandres
 *
 * Created on June 3, 2014, 1:38 AM
 */

#ifndef STATEACTIONTRANSITION_H
#define	STATEACTIONTRANSITION_H

#include "GlobalHeader.h"

#include <cassert>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <boost/thread/shared_mutex.hpp>

#include "QLearning.h"
#include "StateActionTransitionException.h"

using namespace std;

namespace AI {

/**
 * StateTransition
 * <p> This module is represents the possible transition states. Every
 * call to StateTransition::update(state, reward), will increase the
 * value of its frequency and at the same time update the reward value.
 * Call to getNextState would then would return a state on the basis
 * of how likely it occurs. Call to getReward would return the reward
 * of the given state. </p>
 */
template<class S>
class StateActionTransition {
public:
	/**
	 * @param greedy determines how random is getNextState() is. A value of
	 * 1.0 means getNextState returns based on current likelihood of a state
	 * occuring (not random). With 0.0, it will not rely on the likelihood
	 * of state and return a random nextstate.
	 * @param stepSize determines how the frequency is updated. A low value
	 * yields to a more accurate model of the environment but slower in learning
	 * environment. A value of 1.0 yields to forgeting the frequency information
	 * of all other transition states, suitable for deterministic environment.
	 */
	StateActionTransition(const AI::FLOAT greedy, const AI::FLOAT stepSize);

	/**
	 * By adding a new state, this updates the information of all other states.
	 * Frequency of all state, not nextState will decrease and frequency of
	 * nextState will increase. The reward will update the value of the nextState.
	 * @param nextState to be added or increased frequency value and update reward value.
	 * @param reward to update the value of the nextState.
	 */
	virtual void update(const S& nextState, const AI::FLOAT reward);

	/**
	 * Given a state returns its latest reward info.
	 * @param state to be queried of reward.
	 * @return reward of the state.
	 * @throw StateActionTransitionException when given state don't exist.
	 */
	virtual AI::FLOAT getReward(const S& state) const
			throw (StateActionTransitionException);

	/**
	 * @return the possible next state based on its value. Bigger value, better
	 * chance of occuring.
	 * @throw StateActionTransitionException when given state don't exist.
	 */
	virtual const S& getNextState() const throw (StateActionTransitionException);

	/**
	 * @return the number of transition states.
	 */
	size_t getSize() const;

	/**
	 * @param stepSize change the current step size.
	 */
	void setStepSize(AI::FLOAT stepSize);

	/**
	 * @return current step size.
	 */
	AI::FLOAT getStepSize() const;

	/**
	 * @param greedy change the greediness of the current state transition.
	 */
	void setGreedy(AI::FLOAT greedy);

	/**
	 * @return current greediness.
	 */
	AI::FLOAT getGreedy() const;

private:
	bool _findState(const S& state) const;

private:
	// Keeps track of all the possible transistion states and their
	// corresponding frequency and reward.
	map<S, AI::FLOAT> _stateActionTransitionFrequency;
	map<S, AI::FLOAT> _stateActionTransitionReward;

	AI::FLOAT _greedy;
	AI::FLOAT _stepSize;

	mutable std::random_device _randomDevice;
	mutable boost::shared_mutex _frequencyMutex;
	mutable boost::shared_mutex _rewardMutex;
};

template<class S>
StateActionTransition<S>::StateActionTransition(const AI::FLOAT greedy,
		const AI::FLOAT stepSize) :
		_greedy(greedy), _stepSize(stepSize) {
}

template<class S>
void StateActionTransition<S>::update(const S& nextState,
		const AI::FLOAT reward) {
	boost::unique_lock<boost::shared_mutex> rewardLock(_rewardMutex);
	boost::unique_lock<boost::shared_mutex> frequencyLock(_frequencyMutex);

	_stateActionTransitionFrequency.insert(
			std::pair<S, AI::FLOAT>(nextState, 0.0F));
	_stateActionTransitionReward.insert(
			std::pair<S, AI::FLOAT>(nextState, reward));

	// Update Frequency.
	// --Lower the value of all other frequencies.
	for (auto iter = _stateActionTransitionFrequency.begin();
			iter != _stateActionTransitionFrequency.end(); iter++) {
		const S& state = iter->first;
		if (state != nextState) {
			_stateActionTransitionFrequency[state] =
					_stateActionTransitionFrequency[state]
							+ _stepSize
									* (0.0F
											- _stateActionTransitionFrequency[state]);
		}
	}

	// --Increase the value of the next frequency.
	_stateActionTransitionFrequency[nextState] =
			_stateActionTransitionFrequency[nextState]
					+ _stepSize
							* (1.0F - _stateActionTransitionFrequency[nextState]);

	// Note, no need to lower the reward. Updating the reward will suffice.
	_stateActionTransitionReward[nextState] =
			_stateActionTransitionReward[nextState]
					+ 1.0F * (reward - _stateActionTransitionReward[nextState]);

	assert(
			_stateActionTransitionFrequency.size()
					== _stateActionTransitionReward.size());
}

template<class S>
AI::FLOAT StateActionTransition<S>::getReward(const S& state) const
		throw (StateActionTransitionException) {
	boost::shared_lock<boost::shared_mutex> rewardLock(_rewardMutex);
	StateActionTransitionException exception(
			"StateActionTransition<S, AI::FLOAT>::getReward(const S& state): state not yet added.");
	if (_findState(state) == false) {
		throw exception;
	}

	return _stateActionTransitionReward.at(state);;
}

template<class S>
bool StateActionTransition<S>::_findState(const S& state) const {
	boost::shared_lock<boost::shared_mutex> rewardLock(_rewardMutex);
	bool found = _stateActionTransitionFrequency.find(state)
			!= _stateActionTransitionFrequency.end();
	return found;
}

template<class S>
const S& StateActionTransition<S>::getNextState() const
		throw (StateActionTransitionException) {
	boost::shared_lock<boost::shared_mutex> frequencyLock(_frequencyMutex);
	StateActionTransitionException exception(
			"StateActionTransition<S, AI::FLOAT>::getNextState(): nextStates are empty.");
	if (_stateActionTransitionFrequency.size() == 0) {
		throw exception;
	}

	// Get a random number in [0.0,freqValSum].
	std::uniform_real_distribution<AI::FLOAT> distributionRandomSelection(0.0F,
			1.0F);
	AI::FLOAT randomNumberRandomSelection = distributionRandomSelection(
			_randomDevice);

	// If randomNumberRandomSelection > greediness, return a random state.
	if (randomNumberRandomSelection > _greedy) {
		auto it = _stateActionTransitionFrequency.begin();
		std::advance(it,
				_randomDevice() % _stateActionTransitionFrequency.size());
		const S& nextState = it->first;
		return nextState;
	}

	// http://stackoverflow.com/questions/1761626/weighted-random-numbers
	// Acquire the sum of all the frequency values.
	AI::FLOAT freqValSum = 0.0F;
	for (auto iter = _stateActionTransitionFrequency.begin();
			iter != _stateActionTransitionFrequency.end(); iter++) {
		freqValSum += iter->second;
	}

	// Get a random number in [0.0,freqValSum] for weighted selection.
	std::uniform_real_distribution<AI::FLOAT> distributionWeightedSelection(
			0.0F, freqValSum);
	AI::FLOAT randomNumberWeightedSelection = distributionWeightedSelection(
			_randomDevice);

	// Get the one that matches the random value.
	auto iter = _stateActionTransitionFrequency.begin();
	for (; iter != _stateActionTransitionFrequency.end(); iter++) {
		AI::FLOAT currentFreq = iter->second;

		// If current frequency is greater than highest frequency and at the
		// time lower than the current random number then
		// Error = randomNumber-highestFreq is of the lowest, therefore,
		// a candidate.
		if (currentFreq > randomNumberWeightedSelection) {
			return iter->first;
		}

		randomNumberWeightedSelection -= currentFreq;
	}

	assert(false);  // Note supposed to reach here.
}

template<class S>
size_t StateActionTransition<S>::getSize() const {
	return _stateActionTransitionFrequency.size();
}

template<class S>
void StateActionTransition<S>::setStepSize(AI::FLOAT stepSize) {
	this->_stepSize = stepSize;
}

template<class S>
AI::FLOAT StateActionTransition<S>::getStepSize() const {
	return _stepSize;
}

template<class S>
void StateActionTransition<S>::setGreedy(AI::FLOAT greedy) {
	this->_greedy = greedy;
}

template<class S>
AI::FLOAT StateActionTransition<S>::getGreedy() const {
	return _greedy;
}
}

#endif	/* STATEACTIONTRANSITION_H */
