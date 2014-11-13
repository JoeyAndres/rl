CXX=clang++-3.5 -O3
#CXXFLAGS=-Wall -std=c++11 -Wextra -Wshadow
CXXFLAGS=-std=c++14 -Wunused
CPPFLAGS=

INCLUDE_PATHS = -I. -I./UnitTest++	-I./UnitTest++/src -I./UnitTest++/src/Posix -I./UnitTest++/Win32 -I./include -I./test
LIBRARY_PATHS = -L. -L./UnitTest++
AI_LIB_PATH := ./lib/libAI.a

LIBRARY = -lpthread -lUnitTest++ -lboost_system


OBJECT := $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
TEST := $(patsubst test/%.cpp, %,$(wildcard test/*.cpp))

# Compile tests and create library.
all: $(OBJECT) $(TEST) lib

$(TEST): $(OBJECT)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LIBRARY_PATHS) $(INCLUDE_PATHS) $^ -o \
	./build/$@ 	./test/$@.cpp  $(LIBRARY)

lib: $(OBJECT)
	ar rvs $(AI_LIB_PATH) $^

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $(CPPFLAGS) $(LIBRARY_PATHS) $(INCLUDE_PATHS) $^ -o \
	$@ $(LIBRARY)

clean:
	rm -rf $(OBJECT)  $(AI_LIB_PATH)
	$(foreach var,$(TEST), rm -rf ./build/$(var);)
