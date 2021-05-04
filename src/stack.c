#include "stack.h"
#include "linked_list.h"
#include "../core/src/core_single_cardinal.h"

typedef struct _stack{
    linkedList* list;
}stack;

bool  _validStack( stack* _stack );

stack* initStack(){
    stack* newStack;
    newStack = (stack*) malloc( sizeof( stack ) );
    assert( _validStack( newStack ) );

    newStack->list = llInit();
    return newStack;
}

bool  _validStack( stack* _stack ){
    return ( _stack != NULL );
}

int getSizeStack( stack* _stack ){
    if( !stackIsEmpty( _stack ) ){
        return llGetSize( _stack->list );
    }
    return 0;
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


