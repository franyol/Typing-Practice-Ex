CC = gcc
CFLAGS = -Wall -I./include

BIN_DIR = ./bin
TEST_DIR = ./tests

# Static Library
OBJ = $(BIN_DIR)/fsm.o
LIB = $(BIN_DIR)/libfsm.a

# Test files
TEST_SRC = $(wildcard $(TEST_DIR)/*.test.c)
TEST_OBJ = $(TEST_SRC:$(TEST_DIR)/%.test.c=$(BIN_DIR)/%.o)
TEST_BIN = $(TEST_OBJ:$(BIN_DIR)/%.o=$(BIN_DIR)/%.test)

all: $(LIB)

$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)

$(BIN_DIR)/fsm.o: fsm.c
	@mkdir -p $(BIN_DIR)
	$(CC) -c fsm.c $(CFLAGS) -o $(BIN_DIR)/fsm.o

tests: $(TEST_BIN)

$(BIN_DIR)/%.test.o: $(TEST_DIR)/%.test.c
	@mkdir -p $(BIN_DIR)
	$(CC) -c $< $(CFLAGS) -o $@

$(BIN_DIR)/%.test: $(BIN_DIR)/%.test.o $(LIB)
	$(CC) $^ -o $@

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean tests

