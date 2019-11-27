SRC_DIR = ./src
BUILD_DIR = ./build
INC_DIR = -I ./include
BIN_DIR = ./bin
SRC_AUX_DIR = src/aux
ASSETS_DIR = ./assets

CC = gcc
CFLAGS = -w


all: 
	rm -rf $(BUILD_DIR) $(ASSETS_DIR) $(BIN_DIR) || true
	rm ./src/aux/lex.yy.c ./src/aux/y.tab.c ./include/y.tab.h || true
	
	mkdir -p $(ASSETS_DIR) $(BIN_DIR)
	
	flex -o $(SRC_AUX_DIR)/lex.yy.c $(SRC_DIR)/scanner.l
	bison $(SRC_DIR)/parser.y -o $(SRC_AUX_DIR)/y.tab.c --defines=./include/y.tab.h --report=all --report-file=$(ASSETS_DIR)/y.states.out

	$(CC) $(CFLAGS) -o $(BIN_DIR)/parser $(wildcard $(SRC_AUX_DIR)/*) $(SRC_AUX_DIR)/lex.yy.c $(SRC_AUX_DIR)/y.tab.c $(INC_DIR)


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(ASSETS_DIR) $(BIN_DIR) || true
	rm ./src/aux/lex.yy.c ./src/aux/y.tab.c ./include/y.tab.h || true
