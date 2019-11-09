SRC_DIR = ./src
BUILD_DIR = ./build
INC_DIR = -I ./include
BIN_DIR = ./bin
SRC_AUX_DIR = ./src/aux
ASSETS_DIR = ./assets

CC = gcc
CFLAGS = -Wall -g
AUX_SOURCES=$(wildcard src/aux/*.c)
OBJECTS=$(patsubst $(SRC_AUX_DIR)/%.c,$(BUILD_DIR)/%.o, $(AUX_SOURCES))

$(BIN_DIR)/parser: $(OBJECTS)
	mkdir -p $(ASSETS_DIR) $(BIN_DIR)
	flex -o $(SRC_AUX_DIR)/lex.yy.c $(SRC_DIR)/scanner.l
	yacc $(SRC_DIR)/parser.y -o $(SRC_AUX_DIR)/y.tab.c --defines=./include/y.tab.h --report=all --report-file=$(ASSETS_DIR)/y.states.out
	$(CC) $(CFLAGS) -o $@ $^ $(INC_DIR)

$(OBJECTS): $(BUILD_DIR)/%.o : $(SRC_AUX_DIR)/%.c
	makedir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< $(INC_DIR) -o $@


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(ASSETS_DIR) $(BIN_DIR)
	rm $(SRC_AUX_DIR)/lex.yy.c $(SRC_AUX_DIR)/y.tab.c
