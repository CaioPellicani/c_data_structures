#makefile
PROJ_NAME=app

CC=gcc 
FLAG=-Wall
LIBS =-lm

NAMES=stack queue linked_list #double_linked_list order_double_linked_list
#NAMES+=binary_tree
NAMES+=stdHeader
export NAMES

NAME=$(word 3, ${NAMES})

PATH_OBJ=./obj
PATH_SRC=./src
PATH_EXEMPLE=./exemples
PATH_BIN=./bin

OBJS=${PATH_OBJ}/stdHeader.o ${PATH_OBJ}/${NAME}.o 
EXEC_OBJS=${PATH_OBJ}/exemple_${NAME}.o 

ifeq (${NAME}, $(word 1, ${NAMES})) 
	OBJS+=${PATH_OBJ}/linked_list.o
endif
ifeq (${NAME}, $(word 2, ${NAMES}))
	OBJS+=${PATH_OBJ}/linked_list.o
endif

all: test

${PATH_OBJ}/%.o:: ${PATH_SRC}/%.c
	${CC} ${FLAG} -c $^ -o $@
	
${PATH_OBJ}/%.o:: ${PATH_EXEMPLE}/%.c
	${CC} ${FLAG} -c $^ -o $@

${NAME}: ${OBJS} ${EXEC_OBJS}
	${CC} ${FLAG} -o ./${PATH_BIN}/exec_$@ $^

clean:
	rm ${PATH_BIN}/*${NAME}* ${PATH_OBJ}/*${NAME}*

run: ${NAME}
	${PATH_BIN}/exec_$^

name: $(NAME)

test: 
	cd tests && $(MAKE)

ctests: 
	cd tests && $(MAKE) clean

