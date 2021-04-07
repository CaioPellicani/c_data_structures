#ifndef _STACK_H_
#define _STACK_H_

#include "stdHeader.h"

typedef struct _stack stack;

stack* initStack();

bool push( stack* _stack, void* _data );
bool pop( stack* _stack );

void* getTopData( stack* _stack );

bool stackDataUse( stack* _stack, void ( *dataUseFunction ) ( void* data ) );

void emptyStack( stack* _stack );
void deleteStack( stack* _stack );

#endif