# Technical prelude
# See: https://tech.davis-hansson.com/p/make/
SHELL := bash
.ONESHELL:
.SHELLFLAGS := -eu -o pipefail -c
.DELETE_ON_ERROR:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules
ifeq ($(origin .RECIPEPREFIX), undefined)
  $(error This Make does not support .RECIPEPREFIX. Please use GNU Make 4.0 or later)
endif
.RECIPEPREFIX = >

GOOGLE_BENCHMMARK_PREFIX := benchmark/build/src
GOOGLE_BENCHMARK_LIB := libbenchmark.a
GOOGLE_BENCHMARK_PATH := $(addprefix $(GOOGLE_BENCHMMARK_PREFIX)/,$(GOOGLE_BENCHMARK_LIB))

CXX := g++
CXXFLAGS := -O3 -std=c++17 -g -Wall -Wextra
LDFLAGS := -L$(GOOGLE_BENCHMMARK_PREFIX) -lbenchmark -lpthread
INCLUDE := -I ../include -I benchmark/include

HEADERS := $(shell find ../include/useless -name *.hpp -type f)
OBJECTS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

PERF_BINARY := main_perf

.PHONY: all
all: $(GOOGLE_BENCHMARK_PATH) $(PERF_BINARY)
>./$(PERF_BINARY)

%.o: %.cpp $(HEADERS)
>$(CXX) -c $(CXXFLAGS) $(INCLUDE) -o $@ $<

$(PERF_BINARY): $(OBJECTS)
> $(CXX) $(LDFLAGS) -o $@ $^

$(GOOGLE_BENCHMARK_PATH):
> pushd benchmark
> cmake -E make_directory "build"
> cmake \
>	-DCMAKE_BUILD_TYPE=Release \
>	-DGOOGLETEST_PATH=$(realpath googletest) \
>	-S . -B "build"
> cmake --build "build"
> popd

.PHONY: clean
clean:
> rm -rf *.o $(PERF_BINARY)
