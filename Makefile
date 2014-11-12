CXX=clang++-3.5 -O3
#CXXFLAGS=-Wall -std=c++11 -Wextra -Wshadow
CXXFLAGS=-std=c++14 -Wunused
CPPFLAGS=

INCLUDE_PATHS = -I. -I./UnitTest++	-I./UnitTest++/src -I./UnitTest++/src/Posix -I./UnitTest++/Win32 -I./includes
LIBRARY_PATHS = -L. -L./UnitTest++
AI_LIB_PATH := ./lib/libAI.a

LIBRARY = -lpthread -lUnitTest++ -lboost_system


OBJECT := $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
TEST := $(patsubst %.cpp,%.o,$(wildcard Tests/*.cpp))

# Compile tests and create library.
all: $(OBJECT) $(TEST) lib

runF-%:%
	./$^ --output_format=XML --log_level=test_suite > $(^)-report.xml	

run-%:%
	./$^

$(TEST_OBJECT): $(OBJECT)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LIBRARY_PATHS) $(INCLUDE_PATHS) $^ -o \
	$@ $@.cpp  $(LIBRARY)

lib: $(OBJECT)
	ar rvs $(AI_LIB_PATH) $^

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $(CPPFLAGS) $(LIBRARY_PATHS) $(INCLUDE_PATHS) $^ -o \
	$@ $(LIBRARY)

clean:
	rm -f $(OBJECT) $(TEST_OBJECT) $(AI_LIB_PATH)
