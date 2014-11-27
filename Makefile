CXX=g++ -O3
CXXFLAGS=-std=c++14 -Wunused
CPPFLAGS=-m64

INCLUDE_PATHS = -I. -I./UnitTest++	-I./UnitTest++/src -I./UnitTest++/src/Posix -I./UnitTest++/Win32 -I./include -I./test -I./test/etc
LIBRARY_PATHS = -L. -L./UnitTest++
AI_LIB_PATH := ./lib/libAI.a

LIBRARY = -lpthread -lUnitTest++ -lboost_system -larmadillo


OBJECT := $(patsubst src/%.cpp,build/%.o,$(wildcard src/*.cpp))
TEST_OBJECT := $(patsubst test/etc/%.cpp,build/%.o,$(wildcard test/etc/*.cpp))
TEST_EXEC := $(patsubst test/%.cpp, %,$(wildcard test/*.cpp))

# Compile tests and create library.
all: object test_object test lib

object: $(OBJECT)

test_object: $(TEST_OBJECT)

test: $(TEST_EXEC)

$(TEST_EXEC): $(OBJECT) $(TEST_OBJECT)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LIBRARY_PATHS) $(INCLUDE_PATHS) $^ -o \
	./build/exec/$@ ./test/$@.cpp  $(LIBRARY)

lib: $(OBJECT)
	ar rvs $(AI_LIB_PATH) $^

build/%.o:src/%.cpp
	$(CXX) $(CXXFLAGS) -c $(CPPFLAGS) $(LIBRARY_PATHS) $(INCLUDE_PATHS) $^ -o \
	$@ $(LIBRARY)

build/%.o:test/etc/%.cpp
	$(CXX) $(CXXFLAGS) -c $(CPPFLAGS) $(LIBRARY_PATHS) $(INCLUDE_PATHS) $^ -o \
	$@ $(LIBRARY)

run-test:
	$(foreach var,$(TEST_EXEC), echo $(var) && ./build/exec/$(var))

clean:
	rm -rf $(OBJECT)  $(AI_LIB_PATH) $(OBJECT) $(TEST_OBJECT)
	$(foreach var,$(TEST_EXEC),rm -rf build/exec/$(var))
