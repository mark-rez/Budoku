# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

# Source and build directories
SRC_DIR = src
OBJ_DIR = build

# Automatically find all .c files in the src directory
SRC = $(wildcard $(SRC_DIR)/*.c)

# Automatically find corresponding .o files for each .c file
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Executable name
EXEC = budoku

# Default build target
all: $(EXEC)

# Linking the executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compiling source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(EXEC)
