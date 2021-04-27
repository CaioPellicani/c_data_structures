#ifndef _ORDER_LINKED_LIST_H_
#define _ORDER_LINKED_LIST_H_
    #include "../core/src/stdHeader.h"

    typedef struct strOrderLinkedList orderLinkedList;

    orderLinkedList* ollInit( int( *comparison )( void *larger, void *smaller ) );
    void ollDelete( orderLinkedList **__list );

    int ollGetSize( orderLinkedList* _list );
    bool ollIsEmpty( orderLinkedList* _list );

    bool ollInsert( orderLinkedList* _list, void* _data );
    bool ollRemove( orderLinkedList* _list, void *_searchData );

    bool ollDataUse( orderLinkedList* _list, void ( *dataUseFunction ) ( void* data )  );
    void* ollSearch( orderLinkedList* _list, void *_serchaData );

    void ollEmptyList( orderLinkedList* _list );

#endif