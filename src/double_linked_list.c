#include "double_linked_list.h"
#include "../core/src/core_bi_cardinal.h"

#define BOOL_VALID_DLL( LIST ) if( !_dllValidList( LIST ) ){ return false; }
#define BOOL_EMPTY_DLL( LIST ) if( dllIsEmpty( LIST ) ){ return false; }
#define NULL_EMPTY_DLL( LIST ) if( dllIsEmpty( LIST ) ){ return NULL; }

typedef struct strList{
    bNode * head;
    bNode * tail;
    int size;
}doubleLinkedList;

bool _dllValidList( doubleLinkedList* _list );
bool _dllInsertInFontOf( doubleLinkedList* _list, bNode* _thisNode, void* _data );
bool _dllRemoveBNode( doubleLinkedList* _list, bNode* _thisNode );
bNode* _dllGetBNodeAt( doubleLinkedList* _list, int pos );
 
/*  -   EXTERNAL FUNCTIONS  -   */

doubleLinkedList* dllInit(){
    doubleLinkedList* newList = ( typeof( newList ) ) malloc( sizeof( *newList ) );
    assert( _dllValidList( newList ) );
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

int dllGetSize( doubleLinkedList* _list ){
    if( !dllIsEmpty( _list ) ){
        return _list->size;
    }
    return 0;
}

bool dllIsEmpty( doubleLinkedList* _list ){
    BOOL_VALID_DLL( _list );
    return ( _list->head == NULL ) && ( _list->tail == NULL );
}

bool dllPushHead( doubleLinkedList* _list, void* _data ){   
    BOOL_VALID_DLL( _list );
    return _dllInsertInFontOf( _list, _list->head, _data );
}

bool dllPushTail( doubleLinkedList* _list, void* _data ){
    BOOL_VALID_DLL( _list );
    return _dllInsertInFontOf( _list, NULL, _data );
}

bool dllInsertAt( doubleLinkedList* _list, void* _data, int pos ){
    BOOL_VALID_DLL( _list );
    if( pos == _list->size ){
        return _dllInsertInFontOf( _list, NULL, _data );
    }
    bNode* getNode = _dllGetBNodeAt( _list, pos );
    if( getNode != NULL ){
        return _dllInsertInFontOf( _list, getNode, _data );
    }
    return false;
}

bool dllRemoveAt( doubleLinkedList* _list, int pos ){
    BOOL_EMPTY_DLL( _list );
    if( pos == _list->size ){
        return _dllRemoveBNode( _list, _list->tail );
    }
    bNode* getNode = _dllGetBNodeAt( _list, pos );
    if( getNode != NULL ){
        return _dllRemoveBNode( _list, getNode );
    }
    return false;
}

bool dllPopHead( doubleLinkedList* _list ){
    BOOL_EMPTY_DLL( _list );
    return _dllRemoveBNode( _list, _list->head );
}
bool dllPopTail( doubleLinkedList* _list ){
    BOOL_EMPTY_DLL( _list );
    return _dllRemoveBNode( _list, _list->tail );
}

void dllEmptyList( doubleLinkedList* _list ){
    while( _list->head != NULL ){
        dllPopTail( _list );  
    }
}

void* dllGetDataAt( doubleLinkedList* _list, int pos ){
    NULL_EMPTY_DLL( _list );
    return _dllGetBNodeAt( _list, pos )->data;
}

void* dllGetHeadData( doubleLinkedList* _list ){
    NULL_EMPTY_DLL( _list );
    return _list->head->data;
}
void* dllGetTailData( doubleLinkedList* _list ){
    NULL_EMPTY_DLL( _list );
    return _list->tail->data;
}

bool dllDataUse( doubleLinkedList* _list, dataUseFunction dataUseFunc ){
    BOOL_EMPTY_DLL( _list );
    return bNodeDataUse( _list->head, dataUseFunc );
}

void dllDelete( doubleLinkedList** _list ){
    dllEmptyList( *_list );
    free( *_list );
    *_list = NULL;
    assert( *_list == NULL );
}

/*  -   INTERNAL FUNCTIONS  -   */

bool _dllValidList( doubleLinkedList* _list ){
    return ( _list != NULL );
}

bool _dllInsertInFontOf( doubleLinkedList* _list, bNode* _thisNode, void* _data ){
    return insertInFontOf( &_list->head, &_list->tail, &_list->size, _thisNode, _data );
}
bool _dllRemoveBNode( doubleLinkedList* _list, bNode* _thisNode ){
    return removeBNode( &_list->head, &_list->tail, &_list->size, _thisNode ); 
}

bNode* _dllGetBNodeAt( doubleLinkedList* _list, int pos ){
    return getBNodeAt( &_list->head, &_list->tail, &_list->size, pos );
}


