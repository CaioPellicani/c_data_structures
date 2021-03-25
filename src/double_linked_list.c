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
bool pushHead( list* list, void* data ){
    node* newNode;

    if( list == NULL ){
        printf( MSG_NODEF_LIST );
        return false;
    }
    newNode = malloc( sizeof( node ) );
    newNode->data = data;
    
    if( list->head == NULL ){  
        list->head = newNode;
        list->tail = newNode;
    }
    else{
        newNode->nextNode = list->head;
        list->head->prevNode = newNode;
        list->head = newNode;
    }
    return true;
}

bool pushTail( list* list, void* data ){
    node* newNode;

    if( list == NULL ){
        printf( MSG_NODEF_LIST );
        return false;
    }
    newNode = malloc( sizeof( node ) );
    newNode->data = data;
    
    if( list->head == NULL ){  
        list->head = list->tail = newNode;
    }
    else{
        newNode->prevNode = list->tail;
        list->tail->nextNode = newNode;
        list->tail = newNode;
    }
    return true;
}

bool popHead( list* list ){
    if( list == NULL ){
        printf( MSG_NODEF_LIST );
        return false;
    }  
    if( list->head == NULL ){
        printf( MSG_EMPTY_LIST );
        return false;
    }
    else{
        node* deleteNode;
        deleteNode = list->head;

        if( deleteNode->nextNode != NULL ){
            list->head = list->head->nextNode;
            list->head->prevNode = NULL;
        }
        else{
            list->head = list->tail = NULL;
        }
        free( deleteNode->data );
        free( deleteNode );
    }   
    return true;
}
bool popTail( list* list ){
    if( list == NULL ){
        printf( MSG_NODEF_LIST );
        return false;
    }  
    if( list->tail == NULL ){
        printf( MSG_EMPTY_LIST );
        return false;
    }
    else{
        node* deleteNode;
        deleteNode = list->tail;

        if( deleteNode->prevNode != NULL ){
            list->tail = list->tail->prevNode;
            list->tail->nextNode = NULL;
        }
        else{
            list->tail = list->head = NULL;
        }
        free( deleteNode->data );
        free( deleteNode );
    }   
    return true;
}

void emptyList( list* list ){
    while( list->head != NULL ){
        popHead( list );  
    }
}


bool showList( list* list, void (*showData) ( void* data )  ){
    node* seeingNode;

    if( list == NULL ){
        printf( MSG_NODEF_LIST );
        return false;
    }
    if( list->head == NULL ){
        printf( MSG_EMPTY_LIST );
        return false;
    }  

    seeingNode = list->head;
    while ( seeingNode != NULL ){
        showData( ( typeof(seeingNode->data) ) seeingNode->data );
        seeingNode = seeingNode->nextNode;
    }
    return true;
}

void deleteList( list* list ){
    emptyList( list );
    free( list );
    list = NULL;
}


