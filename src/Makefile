CC = gcc
CFLAGS = -Wall -I./fsm/include -I./input/include -I./reader/include
LDFLAGS = -L./fsm/bin -L./input/bin -L./reader/bin -lncurses -lfsm -linput -lreader
LIBS = ./fsm/bin/libfsm.a ./input/bin/libinput.a ./reader/bin/libreader.a

BIN_DIR = ./bin

# Sources
SRCS = main.c
OBJS = $(BIN_DIR)/$(SRCS:.c=.o)
TARGET = $(BIN_DIR)/typing

# Rules
all: $(TARGET)

$(TARGET): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BIN_DIR)/main.o: main.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c main.c -o $(BIN_DIR)/main.o

$(LIBS):
	$(MAKE) -C reader
	$(MAKE) -C input
	$(MAKE) -C fsm

clean:
	rm -rf $(BIN_DIR)
	$(MAKE) -C fsm clean
	$(MAKE) -C input clean
	$(MAKE) -C reader clean

.PHONY: all clean
