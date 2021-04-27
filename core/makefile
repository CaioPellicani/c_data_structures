#makefile libdatastructcore.a
CC=gcc 
FLAG=-Wall
LIB =ar rcs
AR =ar rcs

PATH_CSRC=./src
PATH_COBJ=./obj
PATH_CBIN=./bin
CSRC=$(wildcard ${PATH_CSRC}/*.c)
COBJ=$(patsubst ${PATH_CSRC}/%.c, ${PATH_COBJ}/%.o, ${CSRC})

all: lib

${PATH_COBJ}/%.o: ${PATH_CSRC}/%.c
	${CC} ${FLAG} -c $^ -o $@

lib: ${COBJ}
	${AR} ${PATH_CBIN}/libcore.a ${COBJ}

clean:
	rm -f ${PATH_COBJ}/* ${PATH_CBIN}/*