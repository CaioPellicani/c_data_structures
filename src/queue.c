#include "queue.h"

bool validQueue( queue* _queue, bool _seeIfEmpty );

queue* initQueue(){
    queue* newQueue;
    newQueue = (queue*) malloc( sizeof( queue ) );
    if( newQueue == NULL ){
        printf( MSG_NO_MEM ); 
        return NULL;   
    }
    else{
        return newQueue;
    }
}

bool validQueue( queue* _queue, bool _seeIfEmpty ){
    if( _queue == NULL ){
        printf( MSG_NODEF_QUEUE);
        return false;
    }
    if( ( _seeIfEmpty ) && ( _queue->begin == NULL ) ){
        printf( MSG_EMPTY_QUEUE );
        return false;
    }
    return true;
}

bool push( queue* _queue, void* _data ){
    node* newNode;

    if( validQueue( _queue, false ) ){
        newNode = malloc( sizeof( node ) );
        newNode->data = _data;
        
        if( _queue->begin == NULL ){  
            _queue->begin = _queue->end = newNode;
        }
        else{
            _queue->begin->prevNode = newNode;
            _queue->begin = newNode;
        }
        _queue->size++;
        return true;
    }
    return false;
}

bool pop( queue* _queue ){
    if ( validQueue( _queue, true ) ){

        node* deleteNode;
        deleteNode = _queue->end;

        if( deleteNode->prevNode != NULL ){
            _queue->end = deleteNode->prevNode;
        }
        else{
            _queue->begin = _queue->end = NULL;
        }
        free( deleteNode->data );
        free( deleteNode );
        _queue->size--;
        return true;
    }   
    return false;
}

void* getEndData( queue* _queue ){
    return _queue->end->data;
}

void emptyQueue( queue* _queue ){
    while( _queue->begin != NULL ){
        pop( _queue );  
    }
}

bool showQueue( queue* _queue, void (*showData) ( void* data )  ){
    node* seeingNode;

    if( validQueue( _queue, true ) ){

        seeingNode = _queue->end;
        while ( seeingNode != NULL ){
            showData( seeingNode->data );
            seeingNode = seeingNode->prevNode;
        }
        return true;
    }
    return false;
}

void deleteQueue( queue* _queue ){
    emptyQueue( _queue );
    free( _queue );
    _queue = NULL;
}


