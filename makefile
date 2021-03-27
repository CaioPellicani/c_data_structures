#makefile
PROJ_NAME=app

CC=gcc 
FLAG=-Wall
LIBS =-lm

STD=stdHeader.o 
#NAME=stack
#NAME=queue
NAME=double_linked_list
#NAME=binary_tree



all: ${NAME}

./obj/%.o:: ./src/%.c
	${CC} ${FLAG} -c $^ -o $@
	
./obj/%.o:: ./exemples/%.c
	${CC} ${FLAG} -c $^ -o $@

${NAME}: ./obj/${STD} ./obj/${NAME}.o ./obj/exemple_${NAME}.o
	${CC} ${FLAG} -o ./exec_$@ $^

clean:
	rm *${NAME}* ./obj/*${NAME}*

run: ${NAME}
	./exec_$^ 