CC=gcc
CFLAGS=-std=c99 -Wall -Wextra
EXE=tema1

all: build

build: tema1.c
	$(CC) $^ $(CFLAGS) -o $(EXE)

run: $(EXE)
	./$(EXE)

clean:
	rm -f $(EXE)

.PHONY: clean run

