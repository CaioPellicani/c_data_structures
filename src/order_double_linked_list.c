#include "order_double_linked_list.h"
#include "../core/src/core_bi_cardinal.h"

bNode* _odllSearchBNode( orderDoubleLinkedList *_list, void *_searchValue );
bool _odllInsertInFontOf( orderDoubleLinkedList* _list, bNode* _thisNode, void* _data );
bool _odllRemoveBNode( orderDoubleLinkedList* _list, bNode* _thisNode );
bNode* _odllGetBNodeAt( orderDoubleLinkedList* _list, int pos );

typedef struct strOrderDoubleLinkedList{
    bNode * head;
    bNode * tail;
    int size;
    int( *comparison )( void *larger, void *smaller );
} orderDoubleLinkedList;

orderDoubleLinkedList* odllInit( int( *_comparison )( void *larger, void *smaller ) ){
    orderDoubleLinkedList* newList = ( orderDoubleLinkedList* ) malloc( sizeof( orderDoubleLinkedList ) );
    assert( newList != NULL );

    newList->head = NULL;
    newList->size = 0;
    newList->comparison = _comparison;
    return newList;
}

bool _odllInsertInFontOf( orderDoubleLinkedList* _list, bNode* _thisNode, void* _data ){
    return insertInFontOf( &_list->head, &_list->tail, &_list->size, _thisNode, _data );
}
bool _odllRemoveBNode( orderDoubleLinkedList* _list, bNode* _thisNode ){
    return removeBNode( &_list->head, &_list->tail, &_list->size, _thisNode ); 
}

bNode* _odllGetBNodeAt( orderDoubleLinkedList* _list, int pos ){
    return getBNodeAt( &_list->head, &_list->tail, &_list->size, pos );
}

int odllGetSize( orderDoubleLinkedList* _list ){
    return _list->size;
}

bool odllIsEmpty( orderDoubleLinkedList* _list ){
    return ( _list->head == NULL );
}


bool odllvalidList( orderDoubleLinkedList* _list, bool _seeIfEmpty ){
    if( _list == NULL ){
        die( MSG_NODEF );
    }
    if( ( _seeIfEmpty ) && ( odllIsEmpty( _list ) ) ){
        die( MSG_EMPTY );
    }
    return true;
}

bool odllInsert( orderDoubleLinkedList* _list, void* _data ){
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

bool odllDataUse( orderDoubleLinkedList* _list, void ( *dataUseFunc ) ( void* data )  ){
    assert( _list != NULL );
    assert( ! odllIsEmpty( _list ) );

    return bNodeDataUse( _list->head, dataUseFunc );
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

void* odllSearch( orderDoubleLinkedList* _list, void *_searchData ){
    bNode* seeingNode = _odllSearchBNode( _list, _searchData );
    if( seeingNode != NULL ){
        return seeingNode->data;
    }
    return NULL;
}

bool odllRemove( orderDoubleLinkedList* _list, void *_searchData ){
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

