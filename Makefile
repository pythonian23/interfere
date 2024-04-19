.PHONY: all format clean debug release run

all: format debug

format:
	indent -linux *.c #*.h

clean:
	rm -rf build/

build:
	mkdir -p build

build/main.o: build main.c
	gcc -o build/main.o main.c -c -fpic -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 $(FLAGS)

build/interfere: build build/main.o
	gcc -o build/interfere build/main.o -lraylib -lGL -lm -ldl -lrt -lX11 $(FLAGS)

debug: FLAGS=-g
debug: build/interfere

release: FLAGS=-O3 -DLOG_LEVEL=LOG_WARNING
release: build/interfere
