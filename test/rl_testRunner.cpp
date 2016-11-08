/**
 * rl_testRunner.cpp
 */

#include <cppunit/ui/text/TestRunner.h>

#include "DynaQETWatkins_test.h"
#include "DynaQ_test.h"
#include "QLearningETWatkins_test.h"
#include "SarsaET_test.h"
#include "Softmax_test.h"
#include "StateAction_test.h"
#include "DynaQPrioritizedSweeping_test.h"
#include "Graph_test.h"
#include "QLearningETGD_test.h"
#include "QLearning_test.h"
#include "SarsaETGD_test.h"
#include "Sarsa_test.h"
#include "StateActionTransition_test.h"
#include "TileCode_test.h"
#include "HillClimbing_test.h"

int main(int argc, char** args){
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(DynaQETWatkins_test::suite());
  runner.addTest(DynaQ_test::suite());
  runner.addTest(QLearningETWatkins_test::suite());
  runner.addTest(SarsaET_test::suite());
  runner.addTest(Softmax_test::suite());
  runner.addTest(StateAction_test::suite());
  runner.addTest(DynaQPrioritizedSweeping_test::suite());
  runner.addTest(Graph_test::suite());
  runner.addTest(QLearningETGD_test::suite());
  runner.addTest(QLearning_test::suite());
  runner.addTest(SarsaETGD_test::suite());
  runner.addTest(Sarsa_test::suite());
  runner.addTest(StateActionTransition_test::suite());
  runner.addTest(TileCode_test::suite());
  runner.addTest(HillClimbing_test::suite());
  runner.run();
  return 0;
}
