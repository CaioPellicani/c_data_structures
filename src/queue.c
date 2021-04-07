#include "queue.h"

#define MSG_NO_MEM "Not sufficient memory!\n"
#define MSG_NODEF_QUEUE "Queue is not defined!\n"
#define MSG_EMPTY_QUEUE "The Queue is Empty!\n"

typedef struct node {
    void * data;
    struct node* prevNode;
}node;

typedef struct  _queue{
    node * begin;
    node * end;
    int size;
}queue;

bool validQueue( queue* _queue, bool _seeIfEmpty );
node* newBlankNode();

queue* initQueue(){
    queue* newQueue;
    newQueue = (queue*) malloc( sizeof( queue ) );
    if( newQueue == NULL ){
        die( MSG_NO_MEM );  
    }
    else{
        newQueue->begin = NULL;
        newQueue->end = NULL;
        newQueue->size = NULL;
        return newQueue;
    }
}

node* newBlankNode(){
    node* newNode = malloc( sizeof( node ) );
    newNode->data = NULL;
    newNode->prevNode = NULL;
}

bool validQueue( queue* _queue, bool _seeIfEmpty ){
    if( _queue == NULL ){
        die( MSG_NODEF_QUEUE);
    }
    if( ( _seeIfEmpty ) && ( _queue->begin == NULL ) ){
        die( MSG_EMPTY_QUEUE );
    }
    return true;
}

bool push( queue* _queue, void* _data ){


    if( validQueue( _queue, false ) ){
        node* newNode = newBlankNode();
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


