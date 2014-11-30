CXX=g++ -O3
CXXFLAGS=-std=c++14 -Wunused
CPPFLAGS=
CPP_INTRINSIC_FLAG=-msse4a -ffast-math

INCLUDE_PATHS = -I. -I./UnitTest++ -I./UnitTest++/src -I./UnitTest++/src/Posix -I./UnitTest++/Win32 -I./include -I./test -I./test/etc
LIBRARY_PATHS = -L. -L./UnitTest++
AI_LIB_PATH := ./lib/libAI.a
LIBRARY = -lpthread -lUnitTest++ -lboost_system -larmadillo

FILTER_OUT = $(foreach v,$(2),$(if $(findstring $(1),$(v)),,$(v)))

INTRINSIC_OBJECT := build/GradientDescent.o
TEMP_OBJECT := $(patsubst src/%.cpp,build/%.o,$(wildcard src/*.cpp))
OBJECT := $(call FILTER_OUT,$(INTRINSIC_OBJECT), $(TEMP_OBJECT))
TEST_OBJECT := $(patsubst test/etc/%.cpp,build/%.o,$(wildcard test/etc/*.cpp))
TEST_EXEC := $(patsubst test/%.cpp, build/exec/%,$(wildcard test/*.cpp))

# Compile tests and create library.
all: object test lib

object: $(OBJECT) $(TEST_OBJECT) $(INTRINSIC_OBJECT)

test: $(TEST_EXEC)

lib: $(OBJECT)
	ar rvs $(AI_LIB_PATH) $^

build/%.o:src/%.cpp
	$(CXX) $(CXXFLAGS) -c $(CPPFLAGS) $(INCLUDE_PATHS) $^ -o $@

build/%.o:test/etc/%.cpp
	$(CXX) $(CXXFLAGS) -c $(CPPFLAGS) $(INCLUDE_PATHS) $^ -o $@

build/GradientDescent.o: src/GradientDescent.cpp
	$(CXX) $(CXXFLAGS) -c $(CPPFLAGS) $(CPP_INTRINSIC_FLAG) $(INCLUDE_PATHS) $^ -o $@

build/exec/%:test/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDE_PATHS) $(OBJECT)  \
	$(TEST_OBJECT) $(INTRINSIC_OBJECT) $^ -o $@ $(LIBRARY_PATHS) $(LIBRARY)

run-test:
	$(foreach var,$(TEST_EXEC), echo $(var) && ./build/exec/$(var))

clean:
	rm -rf $(OBJECT)  $(AI_LIB_PATH) $(OBJECT) $(TEST_OBJECT) $(INTRINSIC_OBJECT)
	$(foreach var,$(TEST_EXEC),rm -rf build/exec/$(var))
