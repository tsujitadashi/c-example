CC = gcc
CFLAGS = -O2 -Wall
SOURCES = main.c
OBJECTS = $(SOURCES:%.c=%.o)
TARGET = regex

all: $(TARGET) run

$(TARGET): $(OBJECTS)
		$(CC) -o $@ $^

.c.o:
		$(CC) $(CFLAGS) -c $<

run:
		./$(TARGET)

.PHONY: clean
clean:
		rm -rf $(TARGET) $(OBJECTS)