CC		= gcc
SOURCES = test_unit.c ../players.c ../questions.c ../utils.c
CFLAGS	= -g -w -Wall -Wextra

.PHONY: all

all: clean test_unit

test_unit: test_unit.o ../players.o ../questions.o ../utils.o
	$(CC) $(CFLAGS) -o test_unit test_unit.o ../players.o ../questions.o ../utils.o

clean:
	rm -f test_unit test_unit.o 
