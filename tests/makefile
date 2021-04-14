#makefile DIY unity tests

PATH_LIBS=-L../bin -L../core/bin.
PATH_TSRC=./src
PATH_TOBJ=./obj

TSRC=$(wildcard ${PATH_TSRC}/*.c )
TOBJ=$(patsubst ${PATH_TSRC}/%.c, ${PATH_TOBJ}/%.o, ${TSRC} )
LIBS=-ldatastructs -lcore

all: run_tests

${PATH_TOBJ}/%.o: ${PATH_TSRC}/%.c
	${CC} ${FLAG} -c $^ -o $@

test: ${TOBJ}
	${CC} $^ ${PATH_LIBS} ${LIBS} -o $@ 

run_tests: test
	./test

clean: 
	rm -f ${PATH_TOBJ}/*.o