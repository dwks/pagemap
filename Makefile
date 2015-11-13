# Makefile for pagemap

CC = gcc
CFLAGS = -std=c99

.PHONY: all
all: pagemap pagemap2

pagemap: pagemap.c
	$(CC) $(CFLAGS) $^ -o $@
pagemap2: pagemap2.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	-rm pagemap pagemap2
