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
    int size;
}stack;

stack* initStack();

bool push( stack* _stack, void* _data );
bool pop( stack* _stack );
void emptyStack( stack* _stack );

bool showStack( stack* _stack, void (*showData) ( void* data) );

void deleteStack( stack* _stack );

#endif