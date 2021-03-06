CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99
LFLAGS = 
LIBS = 
SOURCES = jeopardy.c questions.c players.c utils.c
OBJECTS = $(subst .c,.o,$(SOURCES))
EXE = jeopardy.exe
.PHONY: clean help

all : clean $(EXE) cleanup

jeopardy.exe : jeopardy.o questions.o players.o utils.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ 

%.o : %.c
	$(CC) $(CFLAGS) -c $< 

clean:
	rm -f $(OBJECTS) $(EXE) *~

cleanup:
	rm -f $(OBJECTS) *~

help:
	@echo "Valid targets:"
	@echo "  all:    generates all binary files"
	@echo "  clean:  removes .o and .exe files"
	@echo "  to run tests please cd into tests folder and use the Makefile"
