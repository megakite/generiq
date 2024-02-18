CFLAGS	= -Iinclude -std=c11 -Wall -Wextra -Wshadow -Wpedantic -Wconversion 
LDFLAGS =

ifeq ($(DEBUG), 1)
	CFLAGS	+= -Og -g -fsanitize=address -fsanitize=leak
	LDFLAGS	+= -lasan
else
	CFLAGS	+= -O3
endif

SRC_DIR	= ./src
TEST_DIR= ./test
OBJ_DIR	= ./obj
BIN_DIR	= .

SRCS	= $(wildcard $(SRC_DIR)/*.c)
TESTS	= $(wildcard $(TEST_DIR)/*.c)
SRC_OBJ	= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_OBJ= $(TESTS:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

EXEC	= $(TESTS:$(TEST_DIR)/%.c=$(BIN_DIR)/%)

.PHONY: all test clean

all: test

test: $(EXEC)
	$(foreach e, $(EXEC), $(e);)

$(BIN_DIR)/%: $(TEST_DIR)/%.o $(SRC_OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@rm -rvf $(OBJ_DIR) $(EXEC)

-include $(SRC_OBJ:.o=.d)
-include $(TEST_OBJ:.o=.d)
