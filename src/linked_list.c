#include "linked_list.h"
#include "../core/src/core_single_cardinal.h"

#define BOOL_VALID_LL( LIST ) if( !_llValidList( LIST ) ){ return false; }
#define BOOL_EMPTY_LL( LIST ) if( llIsEmpty( LIST ) ){ return false; }

typedef struct strLinkedList{
    node * head;
    int size;
}linkedList;

bool _llValidList( linkedList* _list );

linkedList* llInit(){
    linkedList* newList = ( linkedList* ) malloc( sizeof( linkedList ) );
    assert( _llValidList( newList ) );
    newList->head = NULL;    
    newList->size = 0;
    return newList;
}

bool _llInsertInBetween( linkedList* _list, void *_data, int prevNodePostion ){
    if( prevNodePostion == -1 ){
        return insertInBetween( &_list->head, &_list->size, _data, NULL );        
    }
    node *getNode = getNodeAt( _list->head, prevNodePostion, true, _list->size );
    if( getNode != NULL ){
        return insertInBetween( &_list->head, &_list->size, _data, getNode );
    }
    return NULL;
}

bool _llRemoveNextNode( linkedList* _list, int prevNodePostion ){
    if( prevNodePostion == -1 ){
        return removeNextNode( &_list->head, &_list->size, NULL );       
    }
    node *getNode = getNodeAt( _list->head, prevNodePostion, false, _list->size );
    if( getNode != NULL ){
        return removeNextNode( &_list->head, &_list->size, getNode );
    }
    return NULL;
}

bool _llValidList( linkedList* _list ){
    return ( _list != NULL );
}

int llGetSize( linkedList* _list ){
    if( !llIsEmpty( _list ) ){
        return _list->size;
    }
    return 0;
}

bool llIsEmpty( linkedList* _list ){
    BOOL_VALID_LL( _list );
    return ( _list->head == NULL );
}

bool llPushHead( linkedList* _list, void* _data ){  
    BOOL_VALID_LL( _list );
    return llInsertAt( _list, _data, 0 );
}

bool llPushTail( linkedList* _list, void* _data ){  
    BOOL_VALID_LL( _list );
    return llInsertAt( _list, _data, _list->size - 1 );
}

bool llInsertAt( linkedList* _list, void* _data, int position ){
    BOOL_VALID_LL( _list );
    int prevNodePostion = position - 1;
    return _llInsertInBetween( _list, _data, prevNodePostion );
}

bool llRemoveAt( linkedList* _list, int position ){
    BOOL_EMPTY_LL( _list );
    int prevNodePostion = position - 1;
    return _llRemoveNextNode( _list, prevNodePostion );
}

bool llPopHead( linkedList* _list ){
    BOOL_EMPTY_LL( _list );
    return llRemoveAt( _list, 0 );
}

bool llPopTail( linkedList* _list ){
    BOOL_EMPTY_LL( _list );
    return llRemoveAt( _list, _list->size - 1 );
}

void llEmptyList( linkedList* _list ){
    while( ! llIsEmpty( _list ) ){
        llPopHead( _list );  
    }
}

void* llGetDataAt( linkedList* _list, int position ){
    if( llIsEmpty( _list ) ){
        return NULL;
    }
    return getNodeData( _list->head, position, _list->size );
}

void* llGetHeadData( linkedList* _list ){
    return llGetDataAt( _list, 0 );
}
void* llGetTailData( linkedList* _list ){
    return llGetDataAt( _list, _list->size - 1 );
}

bool llDataUse( linkedList* _list, dataUseFunction dataUseFunc ){
    BOOL_EMPTY_LL( _list );
    return dataUse( _list->head, dataUseFunc );
}

void llDelete( linkedList** _list ){
    llEmptyList( *_list );
    free( *_list );
    *_list = NULL;
    assert( *_list == NULL );
}
