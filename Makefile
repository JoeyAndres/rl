CXX=g++ -O3
CXXFLAGS=-std=c++14 -Wunused
CPPFLAGS=
CPP_INTRINSIC_FLAG:=-ffast-math

# INTRINSICS EXTRA FLAGS
NO_INTRINSIC=-DNO_INTRINSIC
MMX_FLAG= -mmmx -DMMX
SSE_FLAG= -msse -DSSE
SSE2_FLAG= -msse2 -DSSE2
SSE3_FLAG= -msse3 -DSSE3
SSE4_FLAG= -msse4 -DSSE4
SSE4_1_FLAG= -msse4.1 -DSSE4_1
SSE4_2_FLAG= -msse4.2 -DSSE4_2
SSE4A_FLAG= -msse4a -DSSE4A
AVX_FLAG= -mavx -DAVX

INCLUDE_PATHS = -I. -I./UnitTest++ -I./UnitTest++/src -I./UnitTest++/src/Posix -I./UnitTest++/Win32 -I./include -I./test -I./test/etc
LIBRARY_PATHS = -L. -L./UnitTest++
AI_LIB_PATH := ./lib/libAI.a
LIBRARY = -lpthread -lUnitTest++ -lboost_system -larmadillo

FILTER_OUT = $(foreach v,$(2),$(if $(findstring $(1),$(v)),,$(v)))

INTRINSIC_OBJECT := $(patsubst src/intrinsic/%.cpp,build/%.o,$(wildcard src/intrinsic/*.cpp))
OBJECT := $(patsubst src/%.cpp,build/%.o,$(wildcard src/*.cpp))
TEST_OBJECT := $(patsubst test/etc/%.cpp,build/%.o,$(wildcard test/etc/*.cpp))
TEST_EXEC := $(patsubst test/%.cpp, build/exec/%,$(wildcard test/*.cpp))

.PHONY: x86-64-mmx x86-64-sse x86-64-sse2 x86-64-sse3 x86-64-sse4 x86-64-sse4_1 \
	x86-64-sse4_2 x86-64-sse4a x86-64-sse4a-dummy x86-64-avx object clean

# Compile tests and create library.#############################################
default: default_dummy build
default_dummy:
	$(eval CPP_INTRINSIC_FLAG+=$(NO_INTRINSIC))

x86_64_mmx: x86_64_mmx_dummy build
x86_64_mmx_dummy:
	$(eval CPP_INTRINSIC_FLAG+=$(MMX_FLAG))

x86_64_sse: x86_64_sse_dummy build
x86_64_sse_dummy:
	$(eval CPP_INTRINSIC_FLAG+=$(SSE_FLAG))

x86_64_sse2: x86_64_sse2_dummy build
x86_64_sse2_dummy:
	$(eval CPP_INTRINSIC_FLAG+=$(SSE2_FLAG))

x86-64_sse3: x86_64_sse3_dummy build
x86_64_sse3_dummy:
	$(eval CPP_INTRINSIC_FLAG+=$(SSE3_FLAG))

x86-64_sse4: x86_64_sse4_dummy build
x86_64_sse4_dummy:
	$(eval CPP_INTRINSIC_FLAG+=$(SSE4_FLAG))

x86-64_sse4_1: x86_64_sse4_1_dummy build
x86_64_sse4_1_dummy:
	$(eval CPP_INTRINSIC_FLAG+=$(SSE4_1_FLAG))

x86-64_sse4_2: x86_64_sse4_2_dummy build
x86_64_sse4_2_dummy:
	$(eval CPP_INTRINSIC_FLAG+=$(SSE4_2_FLAG)) 	

x86_64_sse4a: x86_64_sse4a_dummy build
x86_64_sse4a_dummy:
	$(eval CPP_INTRINSIC_FLAG+=$(SSE4A_FLAG))

x86_64_avx: x86_64_avx_dummy build
x86_64_avx_dummy:
	$(eval CPP_INTRINSIC_FLAG+=$(AVX_FLAG))
#END_OF_INTRINSIC_TARGETS#######################################################

build: object test

object: $(OBJECT) $(TEST_OBJECT) $(INTRINSIC_OBJECT)

test: $(TEST_EXEC)

lib: $(OBJECT) $(INTRINSIC_OBJECT)
	ar rvs $(AI_LIB_PATH) $^

# Other objects
build/%.o:src/%.cpp
	$(CXX) $(CXXFLAGS) -c $(CPPFLAGS) $(INCLUDE_PATHS) $^ -o $@

# Test objects
build/%.o:test/etc/%.cpp
	$(CXX) $(CXXFLAGS) -c $(CPPFLAGS) $(INCLUDE_PATHS) $^ -o $@

# Intrinsic objects
build/%.o: src/intrinsic/%.cpp
	$(CXX) $(CXXFLAGS) -c $(CPPFLAGS) $(CPP_INTRINSIC_FLAG) $(INCLUDE_PATHS) $^ -o $@

# Executable
build/exec/%:test/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDE_PATHS) $(OBJECT)  \
	$(TEST_OBJECT) $(INTRINSIC_OBJECT) $^ -o $@ $(LIBRARY_PATHS) $(LIBRARY)

run-test:
	$(foreach var,$(TEST_EXEC), echo $(var) && ./build/exec/$(var))

clean:
	rm -rf $(OBJECT)  $(AI_LIB_PATH) $(OBJECT) $(TEST_OBJECT) $(INTRINSIC_OBJECT) $(TEST_EXEC)
