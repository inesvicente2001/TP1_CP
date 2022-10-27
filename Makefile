CC = gcc
BIN = bin/
SRC = src/
INCLUDES = include/
EXEC = k_means

CFLAGS = -O2 -g -lm -Wall -Wextra -Wdouble-promotion -pedantic-errors -Wconversion -march=native -ftree-vectorize

.DEFAULT_GOAL = k_means

k_means: $(SRC)k_means.c
	-p bin
	$(CC) $(CFLAGS) $(SRC)k_means.c -o $(BIN)$(EXEC)

clean:
	rm -r bin/*

run:
	./$(BIN)$(EXEC)