# Makefile for the project

CC = gcc
CFLAGS = -Wall -Wextra -g

# List of source files
SRC = affichage.c combat.c equipe.c main.c structure.c

# Object files
OBJ = $(SRC:.c=.o)

# Output executable
TARGET = projet

# Default target
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean