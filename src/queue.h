#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "stdHeader.h"

typedef struct _queue queue;

queue* initQueue();

bool push( queue* _queue, void* _data );
bool pop( queue* _queue );

void* getEndData( queue* _queue );

void emptyQueue( queue* _queue );
bool showQueue( queue* _queue, void (*showData) ( void* data) );

void deleteQueue( queue* _queue );

#endif