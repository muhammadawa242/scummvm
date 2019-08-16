MODULE := engines/testbed

MODULE_OBJS := \
	config.o \
	config-params.o \
	detection.o \
	events.o \
	fs.o \
	graphics.o \
	midi.o \
	misc.o \
	savegame.o \
	sound.o \
	encoding.o \
	testbed.o \
	testsuite.o

ifdef USE_CLOUD
ifdef USE_LIBCURL
MODULE_OBJS += \
	cloud.o
endif
endif

ifdef USE_SDL_NET
MODULE_OBJS += \
	webserver.o
endif

MODULE_DIRS += \
	engines/testbed

# This module can be built as a plugin
ifeq ($(ENABLE_TESTBED), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
