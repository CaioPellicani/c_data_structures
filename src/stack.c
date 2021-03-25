#include "stack.h"

stack* initStack(){
    stack* newStack;
    newStack = (stack*) malloc( sizeof( stack ) );
    if( newStack == NULL ){
        printf( MSG_NO_MEM ); 
        return NULL;   
    }
    else{
        return newStack;
    }
}

bool push( stack* _stack, void* _data ){
    node* newNode;

    if( _stack == NULL ){
        printf( MSG_NODEF_STACK );
        return false;
    }
    newNode = malloc( sizeof( node ) );
    newNode->data = _data;
    
    if( _stack->top == NULL ){  
        _stack->top = newNode;
    }
    else{
        newNode->prevNode = _stack->top;
        _stack->top = newNode;
    }
    return true;
}

bool pop( stack* _stack ){
    if( _stack == NULL ){
        printf( MSG_NODEF_STACK );
        return false;
    }  
    if( _stack->top == NULL ){
        printf( MSG_EMPTY_STACK );
        return false;
    }
    else{
        node* deleteNode;
        deleteNode = _stack->top;

        if( deleteNode->prevNode != NULL ){
            _stack->top = deleteNode->prevNode;
        }
        else{
            _stack->top = NULL;
        }
        free( deleteNode->data );
        free( deleteNode );
    }   
    return true;
}


void emptyStack( stack* _stack ){
    while( _stack->top != NULL ){
        pop( _stack );  
    }
}

bool showStack( stack* _stack, void (*showData) ( void* data )  ){
    node* seeingNode;

    if( _stack == NULL ){
        printf( MSG_NODEF_STACK );
        return false;
    }
    if( _stack->top == NULL ){
        printf( MSG_EMPTY_STACK );
        return false;
    }  

    seeingNode = _stack->top;
    while ( seeingNode != NULL ){
        showData( seeingNode->data );
        seeingNode = seeingNode->prevNode;
    }
    return true;
}

void deleteStack( stack* _stack ){
    emptyStack( _stack );
    free( _stack );
    _stack = NULL;
}


