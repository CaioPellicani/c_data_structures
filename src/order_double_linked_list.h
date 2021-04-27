#ifndef _ORDER_DOUBLE_LINKED_LIST_
#define _ORDER_DOUBLE_LINKED_LIST_

#include "../core/src/stdHeader.h"

typedef struct strOrderDoubleLinkedList orderDoubleLinkedList;

    orderDoubleLinkedList* odllInit( int( *comparison )( void *larger, void *smaller ) );
    void odllDelete( orderDoubleLinkedList **__list );

    int odllGetSize( orderDoubleLinkedList* _list );
    bool odllIsEmpty( orderDoubleLinkedList* _list );

    bool odllInsert( orderDoubleLinkedList* _list, void* _data );
    bool odllRemove( orderDoubleLinkedList* _list, void *_searchData );

    bool odllDataUse( orderDoubleLinkedList* _list, void ( *dataUseFunc ) ( void* data )  );
    void* odllSearch( orderDoubleLinkedList* _list, void *_serchaData );

    void odllEmptyList( orderDoubleLinkedList* _list );
#endif