#include "order_double_linked_list.h"
#include "double_linked_list.h"
#include "double_linked_list.c"

typedef struct _orderList{
    node ** head;
    node ** tail;
    list * list;
    int * size;
    bool( *comparison )( void *larger, void *smaller );
}orderList;

bool insertInFontOf( list* _list, node* _thisNode, void* data );
bool validList( list* _list, bool _seeIfEmpty );

orderList* initOrderList( bool( *comparison )( void *larger, void *smaller )){
    orderList* newList;
    newList = (orderList*) malloc( sizeof( orderList ) );
    if( newList == NULL ){
        die( MSG_NO_MEM ); 
        return NULL;
    }
    else{
        newList->list = initList();
        newList->comparison = comparison;
        return newList;
    }
}

bool insertInOrder( orderList* _list, void* _data ){
    node* seeingNode = _list->list->head; 

    if( _list->list->head == NULL ){
        pushHead( _list->list, _data );
        return true;
    }
    while( ( _list->comparison( _data, seeingNode->data ) ) && ( seeingNode->nextNode != NULL ) ){
        seeingNode = seeingNode->nextNode;
    }
    if( _list->comparison( _data, seeingNode->data ) ){
        pushTail( _list->list, _data );
        return true;
    }
    insertInFontOf( _list->list, seeingNode, _data );
    return true;
}

bool showOrderList( orderList* _list, void (*showData) ( void* data )  ){
    return showList( _list->list, showData  );
}

void deleteOrderList( orderList* _list ){
    deleteList( _list->list );
    free( _list );
}

