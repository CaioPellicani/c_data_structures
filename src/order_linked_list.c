#include "order_linked_list.h"
#include "../core/src/core.h"

typedef struct strOrderLinkedList{
    node * head;
    int size;
    bool( *comparison )( void *larger, void *smaller );
} orderLinkedList;

orderLinkedList* initOrderLinkedList( bool( *comparison )( void *larger, void *smaller ) ){
    orderLinkedList* newList;

    newList = ( orderLinkedList* ) malloc( sizeof( orderLinkedList ) );

    if( newList == NULL ){
        die( "MSG_NO_MEM" ); 
        return NULL;
    }
    else{
        newList->head = NULL;
        newList->size = 0;
        newList->comparison = comparison;
        return newList;
    }
}

int getOListSize( orderLinkedList* _list ){
    return _list->size;
}

bool oListIsEmpty( orderLinkedList* _list ){
    return ( _list->head == NULL );
}


bool validOList( orderLinkedList* _list, bool _seeIfEmpty ){
    if( _list == NULL ){
        die( MSG_NODEF );
    }
    if( ( _seeIfEmpty ) && ( oListIsEmpty( _list ) ) ){
        die( MSG_EMPTY );
    }
    return true;
}

bool insertInOrder( orderLinkedList* _list, void* _data ){
    node* seeingNode = _list->head; 
    int prevNodePostion = -1;
    if( _list->head == NULL ){
        return insertInBetween( &_list->head,
                                &_list->size,
                                _data, 
                                getNodeAt( _list->head, prevNodePostion, "insert", _list->size ) );
    }
    while( ( _list->comparison( _data, seeingNode->data ) ) && ( seeingNode->nextNode != NULL ) ){
        seeingNode = seeingNode->nextNode;
        prevNodePostion++;
    }
    if( _list->comparison( _data, seeingNode->data ) ){
        prevNodePostion++;
        return insertInBetween( &_list->head,
                                &_list->size,
                                _data, 
                                getNodeAt( _list->head, prevNodePostion, "insert", _list->size ) );
    }

    return insertInBetween( &_list->head,
                            &_list->size,
                            _data, 
                            getNodeAt( _list->head, prevNodePostion, "insert", _list->size ) );
}

bool oListDataUse( orderLinkedList* _list, void ( *dataUseFunction ) ( void* data )  ){
    if( validOList( _list, true ) ){
        return dataUse( _list->head, dataUseFunction );
    }
    return false;
}