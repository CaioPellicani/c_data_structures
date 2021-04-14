#makefile
CC=gcc 
LIB =ar rcs
FLAG=-Wall

NAMES=stack queue linked_list order_linked_list #double_linked_list order_double_linked_list
#NAMES+=binary_tree

NAME=$(word 1, ${NAMES})

PATH_OBJ=./obj
PATH_SRC=./src
PATH_EXEMPLE=./exemples
PATH_BIN=./bin

PATH_LIBS=-Lbin -Lcore/bin
LIBS=-ldatastructs -lcore

SRC=$(foreach n, ${NAMES}, ${PATH_SRC}/${n}.c )
SOBJS=$(patsubst ${PATH_SRC}/%.c, ${PATH_OBJ}/%.o, ${SRC} )

EXEC_OBJS=${PATH_OBJ}/exemple_${NAME}.o 

export CC, FLAG

#all: run 
all: test

${PATH_OBJ}/%.o:: ${PATH_SRC}/%.c
	${CC} ${FLAG} -c $^ -o $@
	
${PATH_OBJ}/%.o:: ${PATH_EXEMPLE}/%.c
	${CC} ${FLAG} -c $^ -o $@

lcore: 
	cd core && $(MAKE)

lib: ${SOBJS} lcore
	${LIB} ${PATH_BIN}/libdatastructs.a ${SOBJS} ./core/bin/libcore.a

${NAME}: lib ${EXEC_OBJS}
	${CC} ${EXEC_OBJS} ${PATH_LIBS} ${LIBS} -o ./${PATH_BIN}/exec_$@ 

clean:
	rm ${PATH_BIN}/*${NAME}* ${PATH_OBJ}/*${NAME}* ${PATH_BIN}/*.a

run: ${NAME}
	${PATH_BIN}/exec_$^

test: lib
	cd tests && $(MAKE)

ctests: 
	cd tests && $(MAKE) clean

