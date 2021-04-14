#ifndef _ORDER_LINKED_LIST_H_
#define _ORDER_LINKED_LIST_H_
    #include "../core/src/stdHeader.h"

    typedef struct strOrderLinkedList orderLinkedList;

    orderLinkedList* initOrderLinkedList( bool( *comparison )( void *larger, void *smaller ) );

    bool insertInOrder( orderLinkedList* _list, void* _data );

    bool oListDataUse( orderLinkedList* _list, void ( *dataUseFunction ) ( void* data )  );

#endif