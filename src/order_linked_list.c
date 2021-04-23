#include "order_linked_list.h"
#include "../core/src/core_s_cardinal.h"

node* searchOListNode( orderLinkedList* _list, void *_searchValue );

typedef struct strOrderLinkedList{
    node * head;
    int size;
    int( *comparison )( void *larger, void *smaller );
} orderLinkedList;

orderLinkedList* initOList( int( *_comparison )( void *larger, void *smaller ) ){
    orderLinkedList* newList = ( orderLinkedList* ) malloc( sizeof( orderLinkedList ) );
    assert( newList != NULL );

    newList->head = NULL;
    newList->size = 0;
    newList->comparison = _comparison;
    return newList;
}

bool oll_insertInBetween( orderLinkedList* _list, void *_data, int prevNodePostion ){
    return insertInBetween( &_list->head,
                            &_list->size,
                            _data, 
                            getNodeAt( _list->head, prevNodePostion, "insert", _list->size ) );
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
        return oll_insertInBetween( _list, _data, prevNodePostion ); 
    }

    while( ( _list->comparison( _data, seeingNode->data ) == LARGER ) && 
           ( seeingNode->nextNode != NULL ) ){

        seeingNode = seeingNode->nextNode;
        prevNodePostion++;
    }

    if( _list->comparison( _data, seeingNode->data ) == LARGER ){
        prevNodePostion++;
        return oll_insertInBetween( _list, _data, prevNodePostion ); 
    }

    return oll_insertInBetween( _list, _data, prevNodePostion ); 
}

bool oListDataUse( orderLinkedList* _list, void ( *dataUseFunction ) ( void* data )  ){
    if( validOList( _list, true ) ){
        return dataUse( _list->head, dataUseFunction );
    }
    return false;
}

node* searchNextNode( orderLinkedList *_list, void *_searchValue ){
    node* seeingNode = _list->head; 
    
    if( _list->comparison( seeingNode->nextNode->data, _searchValue ) == EQUAL ){
        return seeingNode;
    }

    while( ( _list->comparison( seeingNode->nextNode->data, _searchValue ) != EQUAL ) && 
             ( seeingNode->nextNode->nextNode != NULL ) ){
        seeingNode = seeingNode->nextNode;
    }

    if( _list->comparison( seeingNode->nextNode->data, _searchValue ) == EQUAL ){
        return seeingNode;
    }
    return NULL; 
}

void* searchOList( orderLinkedList* _list, void *_searchData ){
    node* seeingNode = searchNextNode( _list, _searchData );
    if( seeingNode != NULL ){
        return seeingNode->nextNode->data;
    }
    if( _list->comparison( _list->head->data, _searchData ) == EQUAL ){
        return _list->head->data;
    }
    return NULL;
}

bool removeInOrder( orderLinkedList* _list, void *_searchData ){
    node* seeingNode = searchNextNode( _list, _searchData );
    if( ( seeingNode != NULL ) || ( _list->comparison( _list->head->data, _searchData ) == EQUAL ) ){
        removeNextNode( &_list->head, &_list->size, seeingNode );
        return true;
    }
    return false;
}

void emptyOList( orderLinkedList* _list ){
    while( ! oListIsEmpty( _list ) ){
        removeNextNode( &_list->head, &_list->size, NULL ); 
    }
}

void deleteOList( orderLinkedList** _list ){
    emptyOList( *_list );
    free( *_list );
    *_list = NULL;
    assert( *_list == NULL );
}

