CC = gcc
CFLAGS = -Wall -I./include -lncurses

BIN_DIR = ./bin
TEST_DIR = ./tests

# Static Library
SRC = $(wildcard *.c)
LIB = $(BIN_DIR)/libreader.a
OBJ = $(SRC:.c=.o)
OBJ_BIN = $(addprefix $(BIN_DIR)/, $(OBJ))

# Test files
TEST_SRC = $(wildcard $(TEST_DIR)/*.test.c)
TEST_OBJ = $(TEST_SRC:$(TEST_DIR)/%.test.c=$(BIN_DIR)/%.o)
TEST_BIN = $(TEST_OBJ:$(BIN_DIR)/%.o=$(BIN_DIR)/%.test)

all: $(LIB)

$(LIB): $(OBJ_BIN)
	ar rcs $(LIB) $^

$(BIN_DIR)/%.o: %.c | $(BIN_DIR)
	$(CC) -c $< $(CFLAGS) -o $@

tests: $(TEST_BIN)

$(BIN_DIR)/%.test.o: $(TEST_DIR)/%.test.c
	@mkdir -p $(BIN_DIR)
	$(CC) -c $< $(CFLAGS) -o $@

$(BIN_DIR)/%.test: $(BIN_DIR)/%.test.o $(LIB)
	$(CC) $^ -o $@

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean tests

