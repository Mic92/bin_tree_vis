VERSION = 0.01
#CC      = /usr/bin/gcc
CFLAGS  = -std=c99 -O3 -Wall -g -D_REENTRANT -DVERSION=\"$(VERSION)\"
LDFLAGS = -lm

OBJ = example_use.o avl_tree_algorithms.o bin_search_tree_algorithms.o bin_tree_vis.o
BIN = example_use

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJ)

