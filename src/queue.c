#include "queue.h"
#include "linked_list.h"

#define MSG_NO_MEM "Not sufficient memory!\n"
#define MSG_NODEF_STACK "Queue is not defined!\n"
#define MSG_EMPTY_STACK "The Queue is Empty!\n"

typedef struct  strQueue{
    linkedList* list;
}queue;

queue* initQueue(){
    queue* newQueue;
    newQueue = ( queue* ) malloc( sizeof( queue ) );
    if( newQueue == NULL ){
        die( MSG_NO_MEM );
        return NULL;  
    }
    else{
        newQueue->list = initLinkedList();
        return newQueue;
    }
}

int getSizeQueue( queue* _queue ){
    return getListSize( _queue->list );
}

bool enqueue( queue* _queue, void* _data ){
    return pushHead( _queue->list, _data );
}

bool dequeue( queue* _queue ){
    return popTail( _queue->list );
}

void* getEndData( queue* _queue ){
    return getTailData( _queue->list );
}

void emptyQueue( queue* _queue ){
    emptyList( _queue->list );
}

bool queueDataUse( queue* _queue, void ( *dataUseFunction ) ( void* data )  ){
    return listDataUse( _queue->list, dataUseFunction );
}

bool queueIsEmpty( queue* _queue ){
    return isEmpty( _queue->list );
}

void deleteQueue( queue** _queue ){
    deleteList( &( *_queue )->list );
    free( *_queue );
    *_queue = NULL;
    assert( *_queue == NULL );
}


