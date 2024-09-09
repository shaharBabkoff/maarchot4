# Makefile

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Targets
TARGET = euler

# Object files
OBJS = graph.o euler.o

# Default target
all: $(TARGET)

# Compile the object files
graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

euler.o: euler.c graph.h
	$(CC) $(CFLAGS) -c euler.c

# Link the object files to create the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Clean the build directory
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean
