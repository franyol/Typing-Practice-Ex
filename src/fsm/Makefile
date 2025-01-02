CC = gcc
CFLAGS = -Wall -I./include

BIN_DIR = ./bin

OBJ = $(BIN_DIR)/fsm.o
LIB = $(BIN_DIR)/libfsm.a

all: $(LIB)

$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)

$(BIN_DIR)/fsm.o: fsm.c
	@mkdir -p $(BIN_DIR)
	$(CC) -c fsm.c $(CFLAGS) -o $(BIN_DIR)/fsm.o

clean:
	rm -rf $(BIN_DIR)
