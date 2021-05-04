#include "order_linked_list.h"
#include "../core/src/core_single_cardinal.h"

node* _ollSearchNode( orderLinkedList* _list, void *_searchValue );
bool _ollInsertInBetween( orderLinkedList* _list, void *_data, int prevNodePostion );
bool _ollRemove( orderLinkedList* _list, void *_searchData );
node* _ollSearchNextNode( orderLinkedList *_list, void *_searchValue );

typedef int( *comparisonFunction )( void *larger, void *smaller );

typedef struct strOrderLinkedList{
    node * head;
    int size;
    comparisonFunction comparison;
} orderLinkedList;

orderLinkedList* ollInit( comparisonFunction _comparison ){
    orderLinkedList* newList = ( orderLinkedList* ) malloc( sizeof( orderLinkedList ) );
    assert( newList != NULL );

    newList->head = NULL;
    newList->size = 0;
    newList->comparison = _comparison;
    return newList;
}

bool _ollInsertInBetween( orderLinkedList* _list, void *_data, int prevNodePostion ){
    if( prevNodePostion == -1 ){
        return insertInBetween( &_list->head, &_list->size, _data, NULL );        
    }

    node *getNode = getNodeAt( _list->head, prevNodePostion, true, _list->size );
    return insertInBetween( &_list->head, &_list->size, _data, getNode );
}

bool _ollRemove( orderLinkedList* _list, void *_searchData ){
    node* seeingNode = _ollSearchNextNode( _list, _searchData );
    if( ( seeingNode != NULL ) || ( _list->comparison( _list->head->data, _searchData ) == EQUAL ) ){
        removeNextNode( &_list->head, &_list->size, seeingNode );
        return true;
    }
    return false;
}


int ollGetSize( orderLinkedList* _list ){
    return _list->size;
}

bool ollIsEmpty( orderLinkedList* _list ){
    return ( _list->head == NULL );
}


bool ollvalidList( orderLinkedList* _list, bool _seeIfEmpty ){
    if( _list == NULL ){
        return false;
    }
    if( ( _seeIfEmpty ) && ( ollIsEmpty( _list ) ) ){
        return false;
    }
    return true;
}

bool ollInsert( orderLinkedList* _list, void* _data ){
    node* seeingNode = _list->head; 
    int prevNodePostion = -1;
    if( _list->head == NULL ){
        return _ollInsertInBetween( _list, _data, prevNodePostion ); 
    }

    while( ( _list->comparison( _data, seeingNode->data ) == LARGER ) && 
           ( seeingNode->nextNode != NULL ) ){

        seeingNode = seeingNode->nextNode;
        prevNodePostion++;
    }

    if( _list->comparison( _data, seeingNode->data ) == LARGER ){
        prevNodePostion++;
        return _ollInsertInBetween( _list, _data, prevNodePostion ); 
    }

    return _ollInsertInBetween( _list, _data, prevNodePostion ); 
}

bool ollDataUse( orderLinkedList* _list, dataUseFunction dataUseFunc ){
    if( ollvalidList( _list, true ) ){
        return dataUse( _list->head, dataUseFunc );
    }
    return false;
}

node* _ollSearchNextNode( orderLinkedList *_list, void *_searchValue ){
    assert( ollvalidList( _list, true ) );
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

void* ollSearch( orderLinkedList* _list, void *_searchData ){
    node* seeingNode = _ollSearchNextNode( _list, _searchData );
    if( seeingNode != NULL ){
        return seeingNode->nextNode->data;
    }
    if( _list->comparison( _list->head->data, _searchData ) == EQUAL ){
        return _list->head->data;
    }
    return NULL;
}

bool ollRemove( orderLinkedList* _list, void *_searchData ){
    return _ollRemove( _list, _searchData );
}

void ollEmptyList( orderLinkedList* _list ){
    while( ! ollIsEmpty( _list ) ){
        removeNextNode( &_list->head, &_list->size, NULL ); 
    }
}

void ollDelete( orderLinkedList** _list ){
    ollEmptyList( *_list );
    free( *_list );
    *_list = NULL;
    assert( *_list == NULL );
}

