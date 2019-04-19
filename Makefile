INTERM=interpreter.c interpreter.h main.c
PROGRAM=./interpreter
CFLAGS=-g -Wall -fsanitize=address
CC = gcc
RM = rm -f


all: $(PROGRAM)

$(PROGRAM): $(INTERM)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(INTERM)

clean:
	$(RM) $(PROGRAM)
