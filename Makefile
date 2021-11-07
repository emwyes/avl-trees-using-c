CC := gcc
CFLAGS := -g -O0 -Wall
FILES_TREE := $(wildcard *tree*.*)
FILES_QUEUE := $(wildcard *queue*)
FILES_ALL:=$(FILES_TREE) $(FILES_QUEUE)

all: trees queue

trees: $(FILES_TREE) queue
	$(CC) $(CFLAGS) $(FILES_TREE) $(FILES_QUEUE) -o avltree

queue: $(FILES_QUEUE)

prt:
	echo $(FILES_QUEUE)

.PHONY: clean
clean:
	rm -f avltree