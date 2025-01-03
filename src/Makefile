CC = gcc
CFLAGS = -Wall -I./fsm/include -I./ui/include -lncurses
LIBS = ./fsm/bin/libfsm.a

BIN_DIR = ./bin

# Sources
SRCS = main.c
OBJS = $(BIN_DIR)/$(SRCS:.c=.o)
TARGET = $(BIN_DIR)/main

# Rules
all: $(TARGET)

$(TARGET): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^ 

$(BIN_DIR)/main.o: main.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c main.c -o $(BIN_DIR)/main.o

$(LIBS):
	$(MAKE) -C fsm

clean:
	rm -rf $(BIN_DIR)
	$(MAKE) -C fsm clean

.PHONY: all clean
