#ifndef _STACK_H_
#define _STACK_H_

#include "stdHeader.h"

#define MSG_NO_MEM "Not sufficient memory!\n"
#define MSG_NODEF_STACK "Stack is not defined!\n"
#define MSG_EMPTY_STACK "The Stack is Empty!\n"

typedef struct node {
    void * data;
    struct node* prevNode;
}node;

typedef struct{
    node * top;
}stack;

stack* initStack();

bool push( stack* stack, void* data );

bool pop( stack* stack );

void emptyStack( stack* stack );

bool showStack( stack* stack, void (*showData) ( void* data) );

void deleteStack( stack* stack );

#endif