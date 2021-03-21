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

CXX := g++
CXXFLAGS := -std=c++17 -g -Wall -Wextra
INCLUDE := -I ../include -I doctest/doctest

HEADERS := $(shell find ../include/useless -name *.hpp -type f)
OBJECTS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

TEST_BINARY := main_test

.PHONY: all
all: $(TEST_BINARY)
> ./$(TEST_BINARY)

%.o: %.cpp $(HEADERS)
>$(CXX) -c $(CXXFLAGS) $(INCLUDE) -o $@ $<

$(TEST_BINARY): $(OBJECTS)
>$(CXX) -o $@ $^

.PHONY: clean
clean:
> rm -rf *.o $(TEST_BINARY)
