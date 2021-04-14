#ifndef _ORDER_DOUBLE_LINKED_LIST_
#define _ORDER_DOUBLE_LINKED_LIST_

#include "../core/src/stdHeader.h"

typedef struct _orderList orderList;

orderList* initOrderList( bool( *comparison )( void *larger, void *smaller ) );

bool insertInOrder( orderList* _list, void* _data );
bool showOrderList( orderList* _list, void (*showData) ( void* data )  );

#endif