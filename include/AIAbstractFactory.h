/**
 * AIAbstractFactory.h
 */

#pragma once

#include "GlobalHeader.h"

#include "Agent.h"

namespace AI{

/*!@class brief AIAbstractFactory
 * @brief Declares the interface for operations that create
 *        abstract product objects.
 */
template<class S, class A>
class AIAbstractFactory {
  Agent<S, A>* createAgent();
};

} // AI
  
