#include "stack.h"
#include "linked_list.h"
#include "linked_list.c"

#define MSG_NODEF_STACK "Stack is not defined!\n"
#define MSG_EMPTY_STACK "The Stack is Empty!\n"

typedef struct _stack{
    linkedList* list;
}stack;

stack* initStack(){
    stack* newStack;
    newStack = (stack*) malloc( sizeof( stack ) );
    if( newStack == NULL ){
        die( MSG_NO_MEM );  
        return false;
    }
    else{
        newStack->list = initList();
        return newStack;
    }
}

bool push( stack* _stack, void* _data ){
    return pushHead( _stack->list, _data );
}

bool pop( stack* _stack ){
    return popHead( _stack->list );
}

void* getTopData( stack* _stack ){
    return getDataAt( _stack->list, 0 );
}

void emptyStack( stack* _stack ){
    emptyList( _stack->list );
}

bool stackDataUse( stack* _stack, void ( *dataUseFunction ) ( void* data )  ){
    return listDataUse( _stack->list, dataUseFunction );
}

void deleteStack( stack* _stack ){
    deleteList( _stack->list );
    free( _stack );
    _stack = NULL;
}


