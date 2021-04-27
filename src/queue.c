#include "queue.h"
#include "double_linked_list.h"

#define MSG_NO_MEM "Not sufficient memory!\n"
#define MSG_NODEF_STACK "Queue is not defined!\n"
#define MSG_EMPTY_STACK "The Queue is Empty!\n"

typedef struct  strQueue{
    doubleLinkedList* list;
}queue;

queue* initQueue(){
    queue* newQueue;
    newQueue = ( queue* ) malloc( sizeof( queue ) );
    if( newQueue == NULL ){
        die( MSG_NO_MEM );
        return NULL;  
    }
    else{
        newQueue->list = dllInit();
        return newQueue;
    }
}

int getSizeQueue( queue* _queue ){
    return dllGetSize( _queue->list );
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

bool queueDataUse( queue* _queue, void ( *dataUseFunction ) ( void* data )  ){
    return dllDataUse( _queue->list, dataUseFunction );
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


