INTERM=interpretor.c interpretor.h main.c
PROGRAM=./interpretor
CFLAGS=-g -Wall -fsanitize=address
CC = gcc
RM = rm -f


all: $(PROGRAM)

$(PROGRAM): $(INTERM)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(INTERM)

clean:
	$(RM) $(PROGRAM)
