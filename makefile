#makefile
CC=gcc 
FLAG=-Wall -g
LIB =ar rcs

NAMES=stack queue linked_list order_linked_list double_linked_list order_double_linked_list
NAMES+=binary_search_tree

NAME=$(word 7, ${NAMES})

PATH_OBJ=./obj
PATH_SRC=./src
PATH_EXEMPLE=./exemples
PATH_BIN=./bin

LIB_NAME=libdatastructs.a
LIB_CORE=-Lcore/bin -lcore
LIB_DS=-Lbin -ldatastructs 
LIBS=${LIB_DS} ${LIB_CORE}

SRC=$(foreach n, ${NAMES}, ${PATH_SRC}/${n}.c )
SOBJS=$(patsubst ${PATH_SRC}/%.c, ${PATH_OBJ}/%.o, ${SRC} )

EXEC_OBJS=${PATH_OBJ}/exemple_${NAME}.o 

export LIB_NAME
export CC
export FLAG
export LIB

#all: run 
all: run_tests

${PATH_OBJ}/%.o:: ${PATH_SRC}/%.c
	${CC} ${FLAG} -c $^ -o $@
	
${PATH_OBJ}/%.o:: ${PATH_EXEMPLE}/%.c
	${CC} ${FLAG} -c $^ -o $@

lcore: 
	cd core && $(MAKE)

lib: lcore ${SOBJS} 
	${LIB} ${PATH_BIN}/${LIB_NAME} ${SOBJS} ./core/bin/libcore.a

${NAME}: lib ${EXEC_OBJS}
	${CC} ${EXEC_OBJS} ${LIBS} -o ./${PATH_BIN}/exec_$@ 

clean:
	cd core && $(MAKE) clean
	rm ${PATH_BIN}/*${NAME}* ${PATH_OBJ}/*${NAME}* ${PATH_BIN}/*.a

run: ${NAME}
	${PATH_BIN}/exec_$^

run_tests: lib
	cd tests && touch ./src/main_tests.c && $(MAKE)

gdb: lib
	cd tests && touch ./src/main_tests.c && $(MAKE) gdb

mtests: lib
	cd tests && touch ./src/main_tests.c && $(MAKE) test	

ctests: 
	cd tests && $(MAKE) clean

