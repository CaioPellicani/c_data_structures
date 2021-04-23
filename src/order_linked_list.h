#ifndef _ORDER_LINKED_LIST_H_
#define _ORDER_LINKED_LIST_H_
    #include "../core/src/stdHeader.h"

    typedef struct strOrderLinkedList orderLinkedList;

    orderLinkedList* initOList( int( *comparison )( void *larger, void *smaller ) );
    int getOListSize( orderLinkedList* _list );
    bool oListIsEmpty( orderLinkedList* _list );

    bool insertInOrder( orderLinkedList* _list, void* _data );

    bool oListDataUse( orderLinkedList* _list, void ( *dataUseFunction ) ( void* data )  );

    void* searchOList( orderLinkedList* _list, void *_serchaData );
    bool removeInOrder( orderLinkedList* _list, void *_searchData );
    void deleteOList( orderLinkedList **__list );

#endif