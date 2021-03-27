#include "stack.h"

bool validStack( stack* _stack, bool _seeIfEmpty );
node* newBlankNode();

stack* initStack(){
    stack* newStack;
    newStack = (stack*) malloc( sizeof( stack ) );
    if( newStack == NULL ){
        die( MSG_NO_MEM );  
    }
    else{
        newStack->top = NULL;
        newStack->size = 0;
        return newStack;
    }
}

node* newBlankNode(){
    node* newNode = malloc( sizeof( node ) );
    newNode->data = NULL;
    newNode->prevNode = NULL;
}

bool validStack( stack* _stack, bool _seeIfEmpty ){
    if( _stack == NULL ){
        die( MSG_NODEF_STACK);
    }
    if( ( _seeIfEmpty ) && ( _stack->top == NULL ) ){
        die( MSG_EMPTY_STACK );
    }
    return true;
}

bool push( stack* _stack, void* _data ){
    if( validStack( _stack, false ) ){
        node* newNode = newBlankNode();
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


