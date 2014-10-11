CXX=g++ -O3
#CXXFLAGS=-Wall -std=c++11 -Wextra -Wshadow
CXXFLAGS=-std=c++11
CPPFLAGS=

INCLUDE_PATHS = -I. -I./Algorithms -I./Tests -I./Tests/RandomWalkTests \
	-I./Algorithms/ReinforcementLearning -I./Algorithms/SupervisedLearning \
	-I./Algorithms/Policy -I./Tests/MountainCarTests -I./UnitTest++ \
	-I./UnitTest++/src -I./UnitTest++/src/Posix -I./boost -I./boost/threadpool \
	-I./Algorithms/Hash -I./Algorithms/Hash/Implementation -I./AIBase
LIBRARY_PATHS = -L. -L./UnitTest++
AI_LIB_PATH := ./lib/libAI.a

LIBRARY = -lpthread -lUnitTest++ -lboost_atomic -lrt -lboost_system -lboost_thread

#$(patsubst %.cpp,%,$(wildcard Tests/SupervisedLearningTest/*_test.cpp))
TEST_OBJECT := $(patsubst %.cpp,%,$(wildcard Tests/*_test.cpp))	

TEST_ENVIRONMENT := $(patsubst %.cpp,%.o,$(wildcard Tests/*.cpp)) \
	$(patsubst %.cpp,%.o,$(wildcard Tests/RandomWalkTests/*.cpp)) \
	$(patsubst %.cpp,%.o,$(wildcard Tests/MountainCarTests/*.cpp))

TEST_ENVIRONMENT := $(filter-out %_test.o, $(TEST_ENVIRONMENT))

TEST_EXECUTABLE := $(patsubst Tests/%, Tests/run-%,$(TEST_OBJECT))	

TESTF_EXECUTABLE := $(patsubst Tests/%, Tests/runF-%,$(TEST_OBJECT))

AI_BASE_OBJECT := $(patsubst %.cpp,%.o,$(wildcard AIBase/*.cpp))

ALGORITHM_OBJECT := $(patsubst %.cpp,%.o,$(wildcard Algorithms/*.cpp)) \
	$(patsubst %.cpp,%.o,$(wildcard Algorithms/ReinforcementLearning/*.cpp)) \
	$(patsubst %.cpp,%.o,$(wildcard Algorithms/SupervisedLearning/*.cpp)) \
	$(patsubst %.cpp,%.o,$(wildcard Algorithms/Policy/*.cpp)) \
	$(patsubst %.cpp,%.o,$(wildcard Algorithms/Hash/*.cpp)) \
	$(patsubst %.cpp,%.o,$(wildcard Algorithms/Hash/Implementation/*.cpp))

ALGORITHM_OBJECT := $(filter-out %TileCodeTest.o, $(ALGORITHM_OBJECT)) \
		$(patsubst %.cpp,%.o,$(wildcard *.cpp))	

OBJECT := $(TEST_ENVIRONMENT) $(ALGORITHM_OBJECT) $(AI_BASE_OBJECT)

# Compile tests and create library.
all: $(OBJECT) $(TEST_OBJECT) lib
	bash CreateHeaderFile.sh

objects: $(OBJECT)

test: $(TEST_EXECUTABLE) 	
test_formatted: $(TESTF_EXECUTABLE) 	

runF-%:%
	./$^ --output_format=XML --log_level=test_suite > $(^)-report.xml	

run-%:%
	./$^

#unit_test_header.pch: /usr/include/boost/test/included/unit_test.hpp
#	$(CXX) $(CXXFLAGS) -c $(CPPFLAGS) $(LIBRARY_PATHS) $(INCLUDE_PATHS) $^ -o $@ -lboost_unit_test_framework


$(TEST_OBJECT): $(OBJECT)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LIBRARY_PATHS) $(INCLUDE_PATHS) $^ -o \
	$@ $@.cpp  $(LIBRARY)

lib: $(OBJECT)
	ar rvs $(AI_LIB_PATH) $^

TileCodeTest: ./Algorithms/SupervisedLearning/TileCodeTest.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LIBRARY_PATHS) $(INCLUDE_PATHS) ./Algorithms/SupervisedLearning/TileCode.h $^ -o \
	$@ $(LIBRARY)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $(CPPFLAGS) $(LIBRARY_PATHS) $(INCLUDE_PATHS) $^ -o \
	$@ $(LIBRARY)

clean:
	rm -f $(OBJECT) $(TEST_OBJECT) $(AI_LIB_PATH)
