CC = gcc
CFLAGS = -Wall -I./fsm/include -I./input/include
LDFLAGS = -L./fsm/bin -L./input/bin -lncurses -lfsm -linput
LIBS = ./fsm/bin/libfsm.a ./input/bin/libinput.a

BIN_DIR = ./bin

# Sources
SRCS = main.c
OBJS = $(BIN_DIR)/$(SRCS:.c=.o)
TARGET = $(BIN_DIR)/main

# Rules
all: $(TARGET)

$(TARGET): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BIN_DIR)/main.o: main.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c main.c -o $(BIN_DIR)/main.o

$(LIBS):
	$(MAKE) -C fsm
	$(MAKE) -C input

clean:
	rm -rf $(BIN_DIR)
	$(MAKE) -C fsm clean
	$(MAKE) -C input clean

.PHONY: all clean
