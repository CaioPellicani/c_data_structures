#include "stack.h"
#include "linked_list.h"
#include "../core/src/core_single_cardinal.h"

#define MSG_NO_MEM "Not sufficient memory!\n"
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
        newStack->list = llInit();
        return newStack;
    }
}

int getSizeStack( stack* _stack ){
    return llGetSize( _stack->list );
}

bool push( stack* _stack, void* _data ){
    return llPushHead( _stack->list, _data );
}

bool pop( stack* _stack ){
    return llPopHead( _stack->list );
}

void* getTopData( stack* _stack ){
    return llGetDataAt( _stack->list, 0 );
}

void emptyStack( stack* _stack ){
    llEmptyList( _stack->list );
}

bool stackDataUse( stack* _stack, dataUseFunction dataUseFunc ){
    return llDataUse( _stack->list, dataUseFunc );
}

bool stackIsEmpty( stack* _stack ){
    return llIsEmpty( _stack->list );
}

void deleteStack( stack** _stack ){
    llDelete( &( *_stack )->list );
    free( *_stack );
    *_stack = NULL;
    assert( *_stack == NULL );
}


