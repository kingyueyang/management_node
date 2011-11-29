all:http_server

CC= gcc -std=c99
FLAGS= -g -Wall -O0
LAB= -levent
BIN=./bin
SRC=./src

http_server.o:src/http_server.c
	${CC} ${FLAGS} -c $< ${SRC}/$@

http_server:src/http_server.o
	${CC} ${FLAGS} -o ${BIN}/$@ $^ ${LAB}

.PYHON:
clean:
	rm -f src/*.o
	rm -f bin/*

