#include "stack.h"

bool validStack( stack* _stack, bool _seeIfEmpty );

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

bool validStack( stack* _stack, bool _seeIfEmpty ){
    if( _stack == NULL ){
        printf( MSG_NODEF_STACK);
        return false;
    }
    if( ( _seeIfEmpty ) && ( _stack->top == NULL ) ){
        printf( MSG_EMPTY_STACK );
        return false;
    }
    return true;
}

bool push( stack* _stack, void* _data ){
    node* newNode;

    if( validStack( _stack, false ) ){
        newNode = malloc( sizeof( node ) );
        newNode->data = _data;
        
        if( _stack->top == NULL ){  
            _stack->top = newNode;
        }
        else{
            newNode->prevNode = _stack->top;
            _stack->top = newNode;
        }
        _stack->size++;
        return true;
    }
    return false;
}

bool pop( stack* _stack ){
    if ( validStack( _stack, true ) ){

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
        _stack->size--;
        return true;
    }   
    return false;
}

void* getTopData( stack* _stack ){
    return _stack->top->data;
}

void emptyStack( stack* _stack ){
    while( _stack->top != NULL ){
        pop( _stack );  
    }
}

bool showStack( stack* _stack, void (*showData) ( void* data )  ){
    node* seeingNode;

    if( validStack( _stack, true ) ){

        seeingNode = _stack->top;
        while ( seeingNode != NULL ){
            showData( seeingNode->data );
            seeingNode = seeingNode->prevNode;
        }
        return true;
    }
    return false;
}

void deleteStack( stack* _stack ){
    emptyStack( _stack );
    free( _stack );
    _stack = NULL;
}


