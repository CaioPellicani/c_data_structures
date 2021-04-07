#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "stdHeader.h"

typedef struct strQueue queue;

queue* initQueue();

bool enqueue( queue* _queue, void* _data );
bool dequeue( queue* _queue );

void* getEndData( queue* _queue );

void emptyQueue( queue* _queue );
bool queueDataUse( queue* _queue, void ( *dataUseFunction ) ( void* data) );

void deleteQueue( queue* _queue );

#endif