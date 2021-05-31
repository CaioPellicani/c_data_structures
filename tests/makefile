#makefile DIY unity tests

LIB_CORE=-L../core/bin -lcore
LIB_DS=-L../bin -ldatastructs 
LIBS=${LIB_DS} ${LIB_CORE}

PATH_TSRC=./src
PATH_TOBJ=./obj

TSRC=$(wildcard ${PATH_TSRC}/*.c )
TOBJ=$(patsubst ${PATH_TSRC}/%.c, ${PATH_TOBJ}/%.o, ${TSRC} )

all: run

${PATH_TOBJ}/%.o: ${PATH_TSRC}/%.c
	${CC} ${FLAG} -c $^ -o $@

test: ${TOBJ}
	${CC} $^ ${LIBS} -o $@ 

run: test
	./test

gdb: test
	gdb ./test -x ./init.gdb

valgrind: test
	valgrind ./test

clean: 
	rm -f ${PATH_TOBJ}/*.o ./test