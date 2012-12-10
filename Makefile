
all: examples

examples: examples/sdl_smile examples/sdl_lines

test: tests/test
	@tests/test

tests/test: tests/test.cpp src/bitcanvas.cpp include/bitcanvas.h
	@g++ -Iinclude tests/test.cpp src/bitcanvas.cpp -o tests/test

examples/sdl_smile: examples/sdl_smile.cpp src/bitcanvas.cpp src/bitcanvas_sdl.cpp include/bitcanvas.h include/bitcanvas.h
	g++ -Iinclude examples/sdl_smile.cpp src/bitcanvas.cpp src/bitcanvas_sdl.cpp -lSDL -o examples/sdl_smile

examples/sdl_lines: examples/sdl_lines.cpp src/bitcanvas.cpp src/bitcanvas_sdl.cpp include/bitcanvas.h include/bitcanvas.h
	g++ -Iinclude examples/sdl_lines.cpp src/bitcanvas.cpp src/bitcanvas_sdl.cpp -lSDL -o examples/sdl_lines

.PHONY: all test examples

