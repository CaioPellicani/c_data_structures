#makefile
PROJ_NAME=app

CC=gcc 
FLAG=-Wall
LIBS =-lm

PATH_OBJ=./obj
PATH_SRC=./src
PATH_EXEMPLE=./exemples
PATH_BIN=./bin

STD=stdHeader.o 
#NAME=stack
#NAME=queue
#NAME=double_linked_list
NAME=binary_tree

all: ${NAME}

${PATH_OBJ}/%.o:: ${PATH_SRC}/%.c
	${CC} ${FLAG} -c $^ -o $@
	
${PATH_OBJ}/%.o:: ${PATH_EXEMPLE}/%.c
	${CC} ${FLAG} -c $^ -o $@

${NAME}: ${PATH_OBJ}/${STD} ${PATH_OBJ}/${NAME}.o ${PATH_OBJ}/exemple_${NAME}.o
	${CC} ${FLAG} -o ./${PATH_BIN}/exec_$@ $^

clean:
	rm ${PATH_BIN}/*${NAME}* ${PATH_OBJ}/*${NAME}*

run: ${NAME}
	./${PATH_BIN}/exec_$^ 