all:http-server

CC= gcc -std=c99
FLAGS= -g -Wall -O0
LAB= -levent
BIN=./bin
SRC=./src

log.o:/src/log.c
	${CC} ${FLAGS} -c $< ${SRC}/$@

http-server.o:src/http-server.c
	${CC} ${FLAGS} -c $< ${SRC}/$@

http-server:src/http-server.o src/log.o
	${CC} ${FLAGS} -o ${BIN}/$@ $^ ${LAB}

.PYHON:
clean:
	rm -f src/*.o
	rm -f bin/*

