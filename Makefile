
# This makefile will build for your local development machine by default,
# using your system-wide g++ and other tools.
# In this mode you can build the examples (if you have the SDL library
# available) and run the tests.
#
# You can also build some of the targets with gcc-avr to target
# AVR microcontrollers. For example, to build the generic library for
# an ATMega328p:
#    make GNUTOOLSPREFIX=avr- MCU=atmega328p
#
# To support a cross-compilation environment the libraries are installed
# in a subdirectory of "lib" named after the target machine, so e.g. if
# you build for AVR it'll be in lib/avr/libbitcanvas.a .

GNU_TOOLS_PREFIX=
MCU="NONE"
CXX=$(GNU_TOOLS_PREFIX)g++
AR=$(GNU_TOOLS_PREFIX)ar
# FIXME: This conditional MCU business doesn't work yet
CXXFLAGS=-Iinclude
#ifeq ($(MCU), NONE)
#	CXXFLAGS=-Iinclude
#else
#	CXXFLAGS=-Iinclude -mmcu=$(MCU)
#endif
GCC_MACHINE:=$(shell $(CXX) -dumpmachine)

GENERIC_HEADERS=include/bitcanvas.h
OBJ_DIR=obj/$(GCC_MACHINE)
LIB_DIR=lib/$(GCC_MACHINE)
GENERIC_LIB_OBJ=$(OBJ_DIR)/bitcanvas.o
GENERIC_LIB=$(LIB_DIR)/libbitcanvas.a

SDL_HEADERS=include/bitcanvas_sdl.h
SDL_LIB_OBJ=$(OBJ_DIR)/bitcanvas_sdl.o
SDL_LIB=$(LIB_DIR)/libbitcanvassdl.a
SDL_EXTERNAL_LIBS=-lSDL

generic_lib: $(GENERIC_LIB)

sdl_lib: $(SDL_LIB)

all: generic_lib sdl_lib examples

examples/sdl_%: examples/sdl_%.cpp $(GENERIC_LIB_OBJ) $(SDL_LIB_OBJ) $(SDL_HEADERS)
	$(CXX) $(CXXFLAGS) $< $(GENERIC_LIB_OBJ) $(SDL_LIB_OBJ) $(SDL_EXTERNAL_LIBS) -o $@

$(OBJ_DIR)/%.o: src/%.cpp obj_dir $(GENERIC_HEADERS) $(SDL_HEADERS)
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(GENERIC_LIB): lib_dir $(GENERIC_LIB_OBJ) $(GENERIC_HEADERS)
	rm -f $@
	$(AR) rcs $@ $(GENERIC_LIB_OBJ)

$(SDL_LIB): lib_dir $(SDL_LIB_OBJ) $(GENERIC_HEADERS) $(SDL_HEADERS)
	rm -f $@
	$(AR) rcs $@ $(GENERIC_LIB_OBJ)

examples: examples/sdl_smile examples/sdl_lines

obj_dir:
	[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)

lib_dir:
	[ -d $(LIB_DIR) ] || mkdir -p $(LIB_DIR)

test: tests/test
	@tests/test

tests/test: tests/test.cpp $(GENERIC_LIB_OBJ) $(GENERIC_HEADERS)
	$(CXX) $(CXXFLAGS) tests/test.cpp -L$(LIB_DIR) -lbitcanvas -o tests/test

show_config:
	@echo Will compile C++ source files with $(CXX) $(CXXFLAGS)
	@echo Will write object files to $(OBJ_DIR)
	@echo Generic library objects will be $(GENERIC_LIB_OBJ)
	@echo SDL library objects will be $(SDL_LIB_OBJ)

clean:
	rm -f $(OBJ_DIR)/*.o

.PHONY: all test examples clean obj_dir lib_dir generic_lib sdl_lib

