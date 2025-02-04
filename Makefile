CC=gcc
CFLAGS=-std=c11  -Werror -Wall -Wconversion -lm

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
TARGET=main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)