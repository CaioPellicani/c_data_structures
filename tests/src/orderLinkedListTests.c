#include "../../src/order_linked_list.h"
#include "minunit.h"
#include "base_tests.h"

orderLinkedList* aList;

void refreshOrderLinkedList(){
    strcpy( result, "\0" );
    oListDataUse( aList, &showData );
}

int runOrderLinkedListTest(){
    INIT_TESTS( "OrderLinkedList", refreshOrderLinkedList );
    aList = initOrderLinkedList( &comparison ); 

    insertInOrder( aList, ( data* )newData( 6 ) );
    EX_STR_EQ( "First InsertInOrder", "6", result );
    //EX_INT_EQ( "size++", 1, getListSize( aList ) );

    insertInOrder( aList, ( data* )newData( 9 ) );
    EX_STR_EQ( "First InsertInOrder", "6 - 9", result );
    //EX_INT_EQ( "size++", 1, getListSize( aList ) );

    insertInOrder( aList, ( data* )newData( 7 ) );
    EX_STR_EQ( "First InsertInOrder", "6 - 7 - 9", result );
    //EX_INT_EQ( "size++", 1, getListSize( aList ) );

    insertInOrder( aList, ( data* )newData( -77 ) );
    EX_STR_EQ( "First InsertInOrder", "-77 - 6 - 7 - 9", result );
    //EX_INT_EQ( "size++", 1, getListSize( aList ) );

    insertInOrder( aList, ( data* )newData( -9 ) );
    EX_STR_EQ( "First InsertInOrder", "-77 - -9 - 6 - 7 - 9", result );
    //EX_INT_EQ( "size++", 1, getListSize( aList ) );
    END_TESTS;
}