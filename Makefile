GCC_FLAGS=-Wall -Wextra -Wpedantic -Werror
CC=gcc

SRC_DIR := src
SOURCES := $(wildcard $(SRC_DIR)/*.c)
BUILDDIR := build
BINDIR := bin
TARGETS := $(patsubst $(SRC_DIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

all: $(TARGETS) | bin
	$(CC) $^ -o bin/editor.out

$(TARGETS): $(BUILDDIR)/%.o: src/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BINDIR): 
	mkdir -p bin

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)
	rm -rf $(BINDIR)