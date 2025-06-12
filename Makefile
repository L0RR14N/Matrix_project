CC = gcc
CFLAGS = -Wall -Wextra -g -I..include -Iinclude
LDFLAGS = -lm
SRC_DIR = src
BIN_DIR = bin

MAIN_SRC = $(SRC_DIR)/main.c
MATRIX_SRCS = $(SRC_DIR)/matrix/matrix.c
OUTPUT_SRCS = $(SRC_DIR)/output/output.c

MAIN_OBJ = $(BIN_DIR)/main.o
MATRIX_OBJ = $(BIN_DIR)/matrix.o
OUTPUT_OBJ = $(BIN_DIR)/output.o

OBJECTS = $(MAIN_OBJ) $(MATRIX_OBJ) $(OUTPUT_OBJ)
TARGET = $(BIN_DIR)/matrix_app

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
		@mkdir -p $(@D)
		$(CC) $(LDFLAGS) $^ -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(@D)
		$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/matrix.o: $(SRC_DIR)/matrix/matrix.c
		@mkdir -p $(@D)
		$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/output.o: $(SRC_DIR)/output/output.c
		@mkdir -p $(@D)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -rf $(BIN_DIR)
