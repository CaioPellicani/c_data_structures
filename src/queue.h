#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "stdHeader.h"

#define MSG_NO_MEM "Not sufficient memory!\n"
#define MSG_NODEF_QUEUE "Queue is not defined!\n"
#define MSG_EMPTY_QUEUE "The Queue is Empty!\n"

typedef struct node {
    void * data;
    struct node* prevNode;
}node;

typedef struct{
    node * begin;
    node * end;
    int size;
}queue;

queue* initQueue();

bool push( queue* _queue, void* _data );
bool pop( queue* _queue );

void* getEndData( queue* _queue );

void emptyQueue( queue* _queue );
bool showQueue( queue* _queue, void (*showData) ( void* data) );

void deleteQueue( queue* _queue );

#endif