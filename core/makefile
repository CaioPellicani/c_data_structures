#makefile libdatastructcore.a

PATH_CSRC=./src
PATH_COBJ=./obj
PATH_CBIN=./bin
CSRC=$(wildcard ${PATH_CSRC}/*.c)
COBJ=$(patsubst ${PATH_CSRC}/%.c, ${PATH_COBJ}/%.o, ${CSRC})

all: lib

${PATH_COBJ}/%.o: ${PATH_CSRC}/%.c
	${CC} ${FLAG} -c $^ -o $@

lib: ${COBJ}
	${LIB} ${PATH_CBIN}/libcore.a ${COBJ}

clean:
	rm -f ${PATH_COBJ}/* ${PATH_CBIN}/*