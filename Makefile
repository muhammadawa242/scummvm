CXX = g++
CC = gcc
AR = ar rcu
CXXFLAGS = -g -W -Wall -Ilua/include `sdl-config --cflags` -DUNIX \
	   -Wno-multichar # -O2
LDFLAGS = -g -W -Wall # -O2
LIBS =  -Llua/lib -llua -llualib `sdl-config --libs` -lz 

# Comment this out for Mac OS X ...
LIBS += -lGL -lGLU

# ... and instead uncomment this if you are on Mac OS X
#CXXFLAGS += -DMACOSX

include Makefile.common

.PHONY: lua-build lua-clean
