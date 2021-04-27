#include "linked_list.h"
#include "../core/src/core_single_cardinal.h"

typedef struct strLinkedList{
    node * head;
    int size;
}linkedList;

bool validList( linkedList* _list, bool _seeIfEmpty );

linkedList* initLinkedList(){
    linkedList* newList = ( linkedList* ) malloc( sizeof( linkedList ) );
    assert( newList != NULL );

    newList->head = NULL;    
    newList->size = 0;
    return newList;
}

bool ll_insertInBetween( linkedList* _list, void *_data, int prevNodePostion ){
    return insertInBetween( &_list->head,
                            &_list->size,
                            _data, 
                            getNodeAt( _list->head, prevNodePostion, "insert", _list->size ) );
}

bool ll_removeNextNode( linkedList* _list, int prevNodePostion ){
    return removeNextNode( &_list->head, 
                           &_list->size, 
                           getNodeAt( _list->head, prevNodePostion, "remove", _list->size ) 
                          );
}

int getListSize( linkedList* _list ){
    return _list->size;
}

bool isEmpty( linkedList* _list ){
    return ( _list->head == NULL );
}

bool pushHead( linkedList* _list, void* _data ){  
    return insertAt( _list, _data, 0 );
}

bool pushTail( linkedList* _list, void* _data ){  
    return insertAt( _list, _data, _list->size - 1 );
}

bool insertAt( linkedList* _list, void* _data, int position ){
    int prevNodePostion = position - 1;
    return ll_insertInBetween( _list, _data, prevNodePostion );
}

bool removeAt( linkedList* _list, int position ){
    int prevNodePostion = position - 1;
    return ll_removeNextNode( _list, prevNodePostion );
}

bool popHead( linkedList* _list ){
    return removeAt( _list, 0 );
}

bool popTail( linkedList* _list ){
    return removeAt( _list, _list->size - 1 );
}

void emptyList( linkedList* _list ){
    while( ! isEmpty( _list ) ){
        popHead( _list );  
    }
}

void* getDataAt( linkedList* _list, int position ){
    return getNodeData( _list->head, position, _list->size );
}

void* getHeadData( linkedList* _list ){
    return getDataAt( _list, 0 );
}
void* getTailData( linkedList* _list ){
    return getDataAt( _list, _list->size - 1 );
}

bool listDataUse( linkedList* _list, void ( *dataUseFunction ) ( void* data )  ){
    assert( _list != NULL );
    assert( ! isEmpty( _list ) );

    return dataUse( _list->head, dataUseFunction );
}

void deleteList( linkedList** _list ){
    emptyList( *_list );
    free( *_list );
    *_list = NULL;
    assert( *_list == NULL );
}
