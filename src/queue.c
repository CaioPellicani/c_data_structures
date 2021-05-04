#include "queue.h"
#include "double_linked_list.h"
#include "../core/src/core_bi_cardinal.h"

typedef struct  strQueue{
    doubleLinkedList* list;
}queue;

bool _validQueue( queue* _queue );

/*  -   EXTERNAL FUNCTIONS  -   */

queue* initQueue(){
    queue* newQueue;
    newQueue = ( queue* ) malloc( sizeof( queue ) );
    assert( _validQueue( newQueue ) );
    newQueue->list = dllInit();
    return newQueue;
}

int getSizeQueue( queue* _queue ){
    if( !queueIsEmpty( _queue ) ){
        return dllGetSize( _queue->list );
    }
    return 0;
}

bool enqueue( queue* _queue, void* _data ){
    return dllPushHead( _queue->list, _data );
}

bool dequeue( queue* _queue ){
    return dllPopTail( _queue->list );
}

void* getEndData( queue* _queue ){
    return dllGetTailData( _queue->list );
}

void emptyQueue( queue* _queue ){
    dllEmptyList( _queue->list );
}

bool queueDataUse( queue* _queue, dataUseFunction dataUseFunc  ){
    return dllDataUse( _queue->list, dataUseFunc );
}

bool queueIsEmpty( queue* _queue ){
    return dllIsEmpty( _queue->list );
}

void deleteQueue( queue** _queue ){
    dllDelete( &( *_queue )->list );
    free( *_queue );
    *_queue = NULL;
    assert( *_queue == NULL );
}

/*  -   INTERNAL FUNCTIONS  -   */

bool _validQueue( queue* _queue ){
    return (_queue != NULL );
}