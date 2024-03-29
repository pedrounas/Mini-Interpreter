INTERM=interpreter.c interpreter.h main.c
PROGRAM=./interpreter
CFLAGS=-g -Wall
CC = gcc
RM = rm -f


all: $(PROGRAM)

$(PROGRAM): $(INTERM)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(INTERM)

clean:
	$(RM) $(PROGRAM)
