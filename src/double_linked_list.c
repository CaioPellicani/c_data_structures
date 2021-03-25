#include "double_linked_list.h"

list* initList(){
    list* newList;
    newList = (list*) malloc( sizeof( list ) );
    if( newList == NULL ){
        printf( MSG_NO_MEM ); 
        return NULL;   
    }
    else{
        return newList;
    }
}
bool pushHead( list* _list, void* _data ){
    node* newNode;

    if( _list == NULL ){
        printf( MSG_NODEF_LIST );
        return false;
    }
    newNode = malloc( sizeof( node ) );
    newNode->data = _data;
    
    if( _list->head == NULL ){  
        _list->head = newNode;
        _list->tail = newNode;
    }
    else{
        newNode->nextNode = _list->head;
        _list->head->prevNode = newNode;
        _list->head = newNode;
    }
    return true;
}

bool pushTail( list* _list, void* _data ){
    node* newNode;

    if( _list == NULL ){
        printf( MSG_NODEF_LIST );
        return false;
    }
    newNode = malloc( sizeof( node ) );
    newNode->data = _data;
    
    if( _list->head == NULL ){  
        _list->head = _list->tail = newNode;
    }
    else{
        newNode->prevNode = _list->tail;
        _list->tail->nextNode = newNode;
        _list->tail = newNode;
    }
    return true;
}

bool popHead( list* _list ){
    if( _list == NULL ){
        printf( MSG_NODEF_LIST );
        return false;
    }  
    if( _list->head == NULL ){
        printf( MSG_EMPTY_LIST );
        return false;
    }
    else{
        node* deleteNode;
        deleteNode = _list->head;

        if( deleteNode->nextNode != NULL ){
            _list->head = _list->head->nextNode;
            _list->head->prevNode = NULL;
        }
        else{
            _list->head = _list->tail = NULL;
        }
        free( deleteNode->data );
        free( deleteNode );
    }   
    return true;
}
bool popTail( list* _list ){
    if( _list == NULL ){
        printf( MSG_NODEF_LIST );
        return false;
    }  
    if( _list->tail == NULL ){
        printf( MSG_EMPTY_LIST );
        return false;
    }
    else{
        node* deleteNode;
        deleteNode = _list->tail;

        if( deleteNode->prevNode != NULL ){
            _list->tail = _list->tail->prevNode;
            _list->tail->nextNode = NULL;
        }
        else{
            _list->tail = _list->head = NULL;
        }
        free( deleteNode->data );
        free( deleteNode );
    }   
    return true;
}

void emptyList( list* _list ){
    while( _list->head != NULL ){
        popHead( _list );  
    }
}


bool showList( list* _list, void (*showData) ( void* data )  ){
    node* seeingNode;

    if( _list == NULL ){
        printf( MSG_NODEF_LIST );
        return false;
    }
    if( _list->head == NULL ){
        printf( MSG_EMPTY_LIST );
        return false;
    }  

    seeingNode = _list->head;
    while ( seeingNode != NULL ){
        showData( ( typeof(seeingNode->data) ) seeingNode->data );
        seeingNode = seeingNode->nextNode;
    }
    return true;
}

void deleteList( list* _list ){
    emptyList( _list );
    free( _list );
    _list = NULL;
}


