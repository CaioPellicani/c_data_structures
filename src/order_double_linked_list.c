#include "order_double_linked_list.h"
#include "../core/src/core_bi_cardinal.h"

#define BOOL_VALID_ODLL( LIST ) if( !_odllValidList( LIST ) ){ return false; }
#define BOOL_EMPTY_ODLL( LIST ) if( odllIsEmpty( LIST ) ){ return false; }
#define NULL_EMPTY_ODLL( LIST ) if( odllIsEmpty( LIST ) ){ return NULL; }

bool _odllValidList( orderDoubleLinkedList* _list );
bNode* _odllSearchBNode( orderDoubleLinkedList *_list, void *_searchValue );
bNode* _odllGetBNodeAt( orderDoubleLinkedList* _list, int pos );
bool _odllInsertInFontOf( orderDoubleLinkedList* _list, bNode* _thisNode, void* _data );
bool _odllRemoveBNode( orderDoubleLinkedList* _list, bNode* _thisNode );

typedef int( *comparisonFunction )( void *larger, void *smaller );

typedef struct strOrderDoubleLinkedList{
    bNode * head;
    bNode * tail;
    int size;
    comparisonFunction comparison;
} orderDoubleLinkedList;

/*  -   INTERNAL FUNCTIONS  -   */

orderDoubleLinkedList* odllInit( comparisonFunction _comparison ){
    orderDoubleLinkedList* newList = ( orderDoubleLinkedList* ) malloc( sizeof( *newList ) );
    assert( _odllValidList( newList ) );
    newList->head = NULL;
    newList->size = 0;
    newList->comparison = _comparison;
    return newList;
}

int odllGetSize( orderDoubleLinkedList* _list ){
    if( !odllIsEmpty( _list ) ){
        return _list->size;
    }
    return 0;
}

bool odllIsEmpty( orderDoubleLinkedList* _list ){
    BOOL_VALID_ODLL( _list );
    return ( _list->head == NULL );
}

bool odllInsert( orderDoubleLinkedList* _list, void* _data ){
    BOOL_VALID_ODLL( _list );
    bNode* seeingNode = _list->head; 

    if( _list->head == NULL ){
        _odllInsertInFontOf( _list, _list->head, _data );
        return true;
    }

    while( ( _list->comparison( _data, seeingNode->data ) == LARGER ) &&
           ( seeingNode->nextNode != NULL )  ){
        seeingNode = seeingNode->nextNode;
    }

    if( _list->comparison( _data, seeingNode->data ) == LARGER ){
        _odllInsertInFontOf( _list, NULL, _data );
        return true;
    }

    _odllInsertInFontOf( _list, seeingNode, _data );
    return true;
}

bool odllDataUse( orderDoubleLinkedList* _list, dataUseFunction dataUseFunc ){
    BOOL_EMPTY_ODLL( _list );
    return bNodeDataUse( _list->head, dataUseFunc );
}

void* odllSearch( orderDoubleLinkedList* _list, void *_searchData ){
    NULL_EMPTY_ODLL( _list );
    bNode* seeingNode = _odllSearchBNode( _list, _searchData );
    if( seeingNode != NULL ){
        return seeingNode->data;
    }
    return NULL;
}

bool odllRemove( orderDoubleLinkedList* _list, void *_searchData ){
    BOOL_EMPTY_ODLL( _list );
    bNode* seeingNode = _odllSearchBNode( _list, _searchData );
    if( seeingNode != NULL ){
        _odllRemoveBNode( _list, seeingNode );
        return true;
    }
    return false;
}

void odllEmptyList( orderDoubleLinkedList* _list ){
    while( ! odllIsEmpty( _list ) ){
        _odllRemoveBNode( _list, _list->head ); 
    }
}

void odllDelete( orderDoubleLinkedList** _list ){
    odllEmptyList( *_list );
    free( *_list );
    *_list = NULL;
    assert( *_list == NULL );
}

/*  -   EXTERNAL FUNCTIONS  -   */

bool _odllValidList( orderDoubleLinkedList* _list ){
    return ( _list != NULL );
}

bNode* _odllSearchBNode( orderDoubleLinkedList *_list, void *_searchValue ){
    bNode* seeingNode = _list->head; 

    while( ( _list->comparison( seeingNode->data, _searchValue ) != EQUAL ) && 
             ( seeingNode->nextNode != NULL ) ){
        seeingNode = seeingNode->nextNode;
    }

    if( _list->comparison( seeingNode->data, _searchValue ) == EQUAL ){
        return seeingNode;
    }
    return NULL; 
}

bNode* _odllGetBNodeAt( orderDoubleLinkedList* _list, int pos ){
    return getBNodeAt( &_list->head, &_list->tail, &_list->size, pos );
}

bool _odllInsertInFontOf( orderDoubleLinkedList* _list, bNode* _thisNode, void* _data ){
    return insertInFontOf( &_list->head, &_list->tail, &_list->size, _thisNode, _data );
}
bool _odllRemoveBNode( orderDoubleLinkedList* _list, bNode* _thisNode ){
    return removeBNode( &_list->head, &_list->tail, &_list->size, _thisNode ); 
}
