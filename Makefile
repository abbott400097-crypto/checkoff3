CC = cc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror -O2

.PHONY: all run test clean

all: build/rle_demo

build:
	mkdir -p build

build/rle_demo: src/rle.c src/rle.h src/demo.c | build
	$(CC) $(CFLAGS) -Isrc src/rle.c src/demo.c -o $@

build/rle_tests: src/rle.c src/rle.h tests/test_rle.c | build
	$(CC) $(CFLAGS) -Isrc src/rle.c tests/test_rle.c -o $@

run: build/rle_demo
	./build/rle_demo

test: build/rle_tests
	./build/rle_tests

clean:
	rm -f build/rle_demo build/rle_tests

