#makefile
#
CC=gcc
FLAG=-Wall

PATH_TSRC=./test_src
PATH_TOBJ=./test_obj
PATH_SSRC=../src
PATH_SOBJ=../obj

#NAMES=stdHeader linked_list stack queue 

TSRC=$(wildcard ${PATH_TSRC}/*.c )
TOBJ=$(patsubst ${PATH_TSRC}/%.c, ${PATH_TOBJ}/%.o, ${TSRC} )
SSRC=$(foreach name, ${NAMES}, ${PATH_SSRC}/${name}.c )
SOBJ=$(patsubst ${PATH_SSRC}/%.c, ${PATH_SOBJ}/%.o, ${SSRC} )

all: run_tests

${PATH_TOBJ}/%.o: ${PATH_TSRC}/%.c
	${CC} ${FLAG} -c $^ -o $@

${PATH_SOBJ}/%.o: ${PATH_SSRC}/%.c
	${CC} ${FLAG} -c $^ -o $@

test: ${SOBJ} ${TOBJ}
	${CC} ${FLAG} -o $@ $^

run_tests: test
	./test

clean: 
	rm -f ${PATH_TOBJ}/*.o