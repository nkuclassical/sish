CFLAGS=-g -Wall -pedantic-errors
sish: sish.o prompt.o process.o parser.o builtin.o
	$(CC) -o sish sish.o prompt.o process.o parser.o builtin.o
sish.o:sish.c sish.h define.h prompt.h parser.h
	$(CC) -c ${CFLAGS} sish.c
prompt.o:prompt.c prompt.h define.h
	$(CC) -c ${CFLAGS} prompt.c
process.o:process.c process.h define.h
	$(CC) -c ${CFLAGS} process.c
parser.o:parser.c parser.h define.h
	$(CC) -c ${CFLAGS} parser.c
builtin.o:builtin.c builtin.h
	$(CC) -c ${CFLAGS} builtin.c


