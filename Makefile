CFLAGS=-g -Wall -pedantic-errors
sish: sish.o prompt.o process.o parser.o builtin.o util.o
	$(CC) -o sish sish.o prompt.o process.o parser.o builtin.o util.o
sish.o:sish.c sish.h define.h prompt.h parser.h
	$(CC) -c ${CFLAGS} sish.c
prompt.o:prompt.c prompt.h define.h
	$(CC) -c ${CFLAGS} prompt.c
process.o:process.c process.h define.h builtin.o parser.o
	$(CC) -c ${CFLAGS} process.c
parser.o:parser.c parser.h define.h util.h 
	$(CC) -c ${CFLAGS} parser.c
builtin.o:builtin.c builtin.h define.h
	$(CC) -c ${CFLAGS} builtin.c
util.o:util.c util.h
	$(CC) -c ${CFLAGS} util.c


