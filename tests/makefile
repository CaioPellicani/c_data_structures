#makefile DIY unity tests
CC=gcc 
FLAG=-Wall
LIB =ar rcs

LIB_CORE=-L../core/bin -lcore
LIB_DS=-L../bin -ldatastructs 
LIBS=${LIB_DS} ${LIB_CORE}

PATH_TSRC=./src
PATH_TOBJ=./obj

TSRC=$(wildcard ${PATH_TSRC}/*.c )
TOBJ=$(patsubst ${PATH_TSRC}/%.c, ${PATH_TOBJ}/%.o, ${TSRC} )

all: test

${PATH_TOBJ}/%.o: ${PATH_TSRC}/%.c
	${CC} ${FLAG} -c $^ -o $@

test: ${TOBJ}
	${CC} $^ ${LIBS} -o $@ 
	./$@ 

clean: 
	rm -f ${PATH_TOBJ}/*.o