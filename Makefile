CC=gcc
CFLAGS=-Wall -Wextra -g
BIN=bin
SRC=src

all: $(BIN)/casino

$(BIN)/casino: $(SRC)/main.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $< -o $@

run: all
	./$(BIN)/casino

clean:
	rm -rf $(BIN)