################################################################################

# Set the shell.
SHELL=/usr/bin/env bash

# Include the configuration.

CXX=`which g++`

PREFIX_LIB=${PYTHIA8}/lib
PREFIX_INCLUDE=${PYTHIA8}/include

CXX_COMMON=-O2 -std=c++11 -pedantic -W -Wall -Wshadow -fPIC

LIB_SUFFIX=.so

CXX_COMMON:=-I$(PREFIX_INCLUDE) $(CXX_COMMON) $(GZIP_LIB)
CXX_COMMON+= -L$(PREFIX_LIB) -Wl,-rpath,$(PREFIX_LIB) -lpythia8 -ldl

PYTHIA=$(PREFIX_LIB)/libpythia8$(LIB_SUFFIX)

################################################################################

# Rules without physical targets (secondary expansion for specific rules).
.SECONDEXPANSION:
.PHONY: all clean

# All targets (no default behavior).
all:
	$(info Usage: make pgun_XX)

# PYTHIA library.
$(PYTHIA):
	$(error Error: PYTHIA must be built, please run "make"\
                in the top PYTHIA directory)

# JVY examples ^_^
pgun%: $(PYTHIA) pgun%.cc
	$(CXX) $@.cc -o $@ $(CXX_COMMON)

# Clean.
clean:
	@rm -f pgun_tau
	@rm -f pgun_Z2tau
