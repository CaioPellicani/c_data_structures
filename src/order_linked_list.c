#include "order_linked_list.h"
#include "../core/src/core_single_cardinal.h"

#define BOOL_VALID_OLL( LIST ) if( !_ollValidList( LIST ) ){ return false; }
#define BOOL_EMPTY_OLL( LIST ) if( ollIsEmpty( LIST ) ){ return false; }
#define NULL_EMPTY_OLL( LIST ) if( ollIsEmpty( LIST ) ){ return NULL; }

bool _ollValidList( orderLinkedList *_list );
node* _ollSearchNextNode( orderLinkedList *_list, void *_searchValue );
bool _ollInsertInBetween( orderLinkedList* _list, void *_data, int prevNodePostion );
bool _ollRemove( orderLinkedList* _list, void *_searchData );

typedef int( *comparisonFunction )( void *larger, void *smaller );

typedef struct strOrderLinkedList{
    node * head;
    int size;
    comparisonFunction comparison;
} orderLinkedList;

/*  -   EXTERNAL FUNCTIONS  -   */

orderLinkedList* ollInit( comparisonFunction _comparison ){
    orderLinkedList* newList = ( orderLinkedList* ) malloc( sizeof( orderLinkedList ) );
    assert( _ollValidList( newList ) );
    newList->head = NULL;
    newList->size = 0;
    newList->comparison = _comparison;
    return newList;
}

int ollGetSize( orderLinkedList* _list ){
    if( !ollIsEmpty( _list ) ){
        return _list->size;
    }
    return 0;
}

bool ollIsEmpty( orderLinkedList* _list ){
    BOOL_VALID_OLL( _list );
    return ( _list->head == NULL );
}

bool ollInsert( orderLinkedList* _list, void* _data ){
    BOOL_VALID_OLL( _list );
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
    BOOL_EMPTY_OLL( _list );
    return dataUse( _list->head, dataUseFunc );
}

void* ollSearch( orderLinkedList* _list, void *_searchData ){
    NULL_EMPTY_OLL( _list );
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

/*  -   INTERNAL FUNCTIONS  -   */

bool _ollValidList( orderLinkedList *_list ){
    return ( _list != NULL );
}

bool _ollInsertInBetween( orderLinkedList* _list, void *_data, int prevNodePostion ){
    if( prevNodePostion == -1 ){
        return insertInBetween( &_list->head, &_list->size, _data, NULL );        
    }

    node *getNode = getNodeAt( _list->head, prevNodePostion, true, _list->size );
    return insertInBetween( &_list->head, &_list->size, _data, getNode );
}

node* _ollSearchNextNode( orderLinkedList *_list, void *_searchValue ){
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

bool _ollRemove( orderLinkedList* _list, void *_searchData ){
    node* seeingNode = _ollSearchNextNode( _list, _searchData );
    if( ( seeingNode != NULL ) || ( _list->comparison( _list->head->data, _searchData ) == EQUAL ) ){
        removeNextNode( &_list->head, &_list->size, seeingNode );
        return true;
    }
    return false;
}

