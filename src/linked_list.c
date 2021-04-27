#include "linked_list.h"
#include "../core/src/core_single_cardinal.h"

typedef struct strLinkedList{
    node * head;
    int size;
}linkedList;

bool _llvalidList( linkedList* _list, bool _seeIfEmpty );

linkedList* llInit(){
    linkedList* newList = ( linkedList* ) malloc( sizeof( linkedList ) );
    assert( newList != NULL );

    newList->head = NULL;    
    newList->size = 0;
    return newList;
}

bool _llInsertInBetween( linkedList* _list, void *_data, int prevNodePostion ){
    return insertInBetween( &_list->head,
                            &_list->size,
                            _data, 
                            getNodeAt( _list->head, prevNodePostion, "insert", _list->size ) );
}

bool _llRemoveNextNode( linkedList* _list, int prevNodePostion ){
    return removeNextNode( &_list->head, 
                           &_list->size, 
                           getNodeAt( _list->head, prevNodePostion, "remove", _list->size ) 
                          );
}

int llGetSize( linkedList* _list ){
    return _list->size;
}

bool llIsEmpty( linkedList* _list ){
    return ( _list->head == NULL );
}

bool llPushHead( linkedList* _list, void* _data ){  
    return llInsertAt( _list, _data, 0 );
}

bool llPushTail( linkedList* _list, void* _data ){  
    return llInsertAt( _list, _data, _list->size - 1 );
}

bool llInsertAt( linkedList* _list, void* _data, int position ){
    int prevNodePostion = position - 1;
    return _llInsertInBetween( _list, _data, prevNodePostion );
}

bool llRemoveAt( linkedList* _list, int position ){
    int prevNodePostion = position - 1;
    return _llRemoveNextNode( _list, prevNodePostion );
}

bool llPopHead( linkedList* _list ){
    return llRemoveAt( _list, 0 );
}

bool llPopTail( linkedList* _list ){
    return llRemoveAt( _list, _list->size - 1 );
}

void llEmptyList( linkedList* _list ){
    while( ! llIsEmpty( _list ) ){
        llPopHead( _list );  
    }
}

void* llGetDataAt( linkedList* _list, int position ){
    return getNodeData( _list->head, position, _list->size );
}

void* llGetHeadData( linkedList* _list ){
    return llGetDataAt( _list, 0 );
}
void* llGetTailData( linkedList* _list ){
    return llGetDataAt( _list, _list->size - 1 );
}

bool llDataUse( linkedList* _list, void ( *dataUseFunction ) ( void* data )  ){
    assert( _list != NULL );
    assert( ! llIsEmpty( _list ) );

    return dataUse( _list->head, dataUseFunction );
}

void llDelete( linkedList** _list ){
    llEmptyList( *_list );
    free( *_list );
    *_list = NULL;
    assert( *_list == NULL );
}
