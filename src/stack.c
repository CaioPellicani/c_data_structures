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

bool push( stack* stack, void* data ){
    node* newNode;

    if( stack == NULL ){
        printf( MSG_NODEF_STACK );
        return false;
    }
    newNode = malloc( sizeof( node ) );
    newNode->data = data;
    
    if( stack->top == NULL ){  
        stack->top = newNode;
    }
    else{
        newNode->prevNode = stack->top;
        stack->top = newNode;
    }
    return true;
}

bool pop( stack* stack ){
    if( stack == NULL ){
        printf( MSG_NODEF_STACK );
        return false;
    }  
    if( stack->top == NULL ){
        printf( MSG_EMPTY_STACK );
        return false;
    }
    else{
        node* deleteNode;
        deleteNode = stack->top;

        if( deleteNode->prevNode != NULL ){
            stack->top = deleteNode->prevNode;
        }
        else{
            stack->top = NULL;
        }
        free( deleteNode->data );
        free( deleteNode );
    }   
    return true;
}


void emptyStack( stack* stack ){
    while( stack->top != NULL ){
        pop( stack );  
    }
}

bool showStack( stack* stack, void (*showData) ( void* data )  ){
    node* seeingNode;

    if( stack == NULL ){
        printf( MSG_NODEF_STACK );
        return false;
    }
    if( stack->top == NULL ){
        printf( MSG_EMPTY_STACK );
        return false;
    }  

    seeingNode = stack->top;
    while ( seeingNode != NULL ){
        showData( ( typeof(seeingNode->data) ) seeingNode->data );
        seeingNode = seeingNode->prevNode;
    }
    return true;
}

void deleteStack( stack* stack ){
    emptyStack( stack );
    free( stack );
    stack = NULL;
}


