
all:

test: tests/test
	@tests/test

tests/test: tests/test.cpp src/bitcanvas.cpp include/bitcanvas.h
	@g++ -Iinclude tests/test.cpp src/bitcanvas.cpp -o tests/test

.PHONY: all test

