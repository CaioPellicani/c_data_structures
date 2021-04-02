#ifndef _ORDER_DOUBLE_LINKED_LIST_
#define _ORDER_DOUBLE_LINKED_LIST_

#include "stdHeader.h"
#include "double_linked_list.h"

typedef struct{
    node ** head;
    node ** tail;
    list * list;
    int * size;
    bool( *comparison )( void *larger, void *smaller );
}orderList;

orderList* initOrderList( bool( *comparison )( void *larger, void *smaller ) );

bool insertInOrder( orderList* _list, void* _data );
bool showOrderList( orderList* _list, void (*showData) ( void* data )  );

#endif