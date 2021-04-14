#include "../../src/order_linked_list.h"
#include "minunit.h"
#include "base_tests.h"

orderLinkedList* aList;

void refreshOrderLinkedList(){
    strcpy( result, "\0" );
    listDataUse( aList, &showData );
}

int runOrderLinkedListTest(){
    INIT_TESTS( "OrderLinkedList", refreshOrderLinkedList );
    aList = initOrderLinkedList( &comparison ); 

    END_TESTS;
}