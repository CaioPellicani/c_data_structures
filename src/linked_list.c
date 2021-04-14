#include "linked_list.h"
#include "../core/src/core.h"

#define MSG_NO_MEM "Not sufficient memory!\n"
#define MSG_NODEF "List is not defined!\n"
#define MSG_EMPTY "The List is Empty!\n"
#define MGS_OUT_RANGE(TYPE) "\n\nNot possible to %s. Position '%d' is out ouf range.\n", TYPE, position + 1 

typedef struct strLinkedList{
    node * head;
    int size;
}linkedList;

bool validList( linkedList* _list, bool _seeIfEmpty );

linkedList* initLinkedList(){
    linkedList* newList;
    newList = ( linkedList* ) malloc( sizeof( linkedList ) );
    assert( newList != NULL );
        newList->head = NULL;
        newList->size = 0;
    return newList;
}

int getListSize( linkedList* _list ){
    return _list->size;
}

bool isEmpty( linkedList* _list ){
    return ( _list->head == NULL );
}

bool validList( linkedList* _list, bool _seeIfEmpty ){
    if( _list == NULL ){
        die( MSG_NODEF );
    }
    if( ( _seeIfEmpty ) && ( isEmpty( _list ) ) ){
        die( MSG_EMPTY );
    }

    return true;
}

bool pushHead( linkedList* _list, void* _data ){  
    return insertAt( _list, _data, 0 );
}

bool pushTail( linkedList* _list, void* _data ){  
    return insertAt( _list, _data, _list->size - 1 );
}

bool insertAt( linkedList* _list, void* _data, int position ){
    int prevNodePostion = position - 1;
    return insertInBetween( &_list->head,
                             &_list->size,
                             _data, 
                             getNodeAt( _list->head, prevNodePostion, "insert", _list->size ) 
                            );
}

bool removeAt( linkedList* _list, int position ){
    int prevNodePostion = position - 1;
    return removeNextNode( &_list->head, 
                            &_list->size, 
                           getNodeAt( _list->head, prevNodePostion, "remove", _list->size ) 
                          );
}

bool popHead( linkedList* _list ){
    return removeAt( _list, 0 );
}

bool popTail( linkedList* _list ){
    return removeAt( _list, _list->size - 1 );
}

void emptyList( linkedList* _list ){
    while( _list->head != NULL ){
        popHead( _list );  
    }
}

void* getDataAt( linkedList* _list, int position ){
    int prevNodePostion = position;
    node* result = getNodeAt( _list->head, prevNodePostion, "get data", _list->size );

    if ( result == NULL ){
        return _list->head->data;
    }
    else{
        return result->data;
    }
}

void* getHeadData( linkedList* _list ){
    return getDataAt( _list, 0 );
}
void* getTailData( linkedList* _list ){
    return getDataAt( _list, _list->size - 1 );
}

bool listDataUse( linkedList* _list, void ( *dataUseFunction ) ( void* data )  ){
    node* seeingNode;

    if( validList( _list, true ) ){
        seeingNode = _list->head;
        while ( seeingNode != NULL ){
            dataUseFunction( seeingNode->data );
            seeingNode = seeingNode->nextNode;
        }
        return true;
    }
    return false;
}

void deleteList( linkedList* _list ){
    emptyList( _list );
    free( _list );
    _list = NULL;
    assert( _list == NULL );
}
