#include "../../src/order_linked_list.h"
#include "orderLinkedListTests.h"
#include "minunit.h"
#include "base_tests.h"

orderLinkedList* aList;

void refreshOrderLinkedList(){
    strcpy( result, "\0" );
    oListDataUse( aList, &showData );
}

int runOrderLinkedListTest(){
    INIT_TESTS( "OrderLinkedList", refreshOrderLinkedList );
    aList = initOList( &comparison ); 
    EX_NOT_NULL( "init", aList ); 

    insertInOrder( aList, ( data* )newData( 6 ) );
    EX_STR_EQ( "First InsertInOrder", "6", result );
    EX_INT_EQ( "size++", 1, getOListSize( aList ) );

    insertInOrder( aList, ( data* )newData( 9 ) );
    EX_STR_EQ( "First InsertInOrder", "6 - 9", result );
    EX_INT_EQ( "size++", 2, getOListSize( aList ) );

    insertInOrder( aList, ( data* )newData( 7 ) );
    EX_STR_EQ( "First InsertInOrder", "6 - 7 - 9", result );
    EX_INT_EQ( "size++", 3, getOListSize( aList ) );

    insertInOrder( aList, ( data* )newData( -77 ) );
    EX_STR_EQ( "First InsertInOrder", "-77 - 6 - 7 - 9", result );
    EX_INT_EQ( "size++", 4, getOListSize( aList ) );

    data* searchTemplate = newData( 6 );
    data* dataSearch = ( data* ) searchOList( aList, searchTemplate );
    EX_INT_EQ( "Search", 6, dataSearch->value );

    searchTemplate->value = 5;
    dataSearch = ( data* ) searchOList( aList, searchTemplate );
    EX_NULL( "Search fail", dataSearch );

    insertInOrder( aList, ( data* )newData( -9 ) );
    EX_STR_EQ( "First InsertInOrder", "-77 - -9 - 6 - 7 - 9", result );
    EX_INT_EQ( "size++", 5, getOListSize( aList ) );

    searchTemplate->value = 6;
    removeInOrder( aList, searchTemplate );
    EX_STR_EQ( "First RemoveInOrder", "-77 - -9 - 7 - 9", result );
    EX_INT_EQ( "size--", 4, getOListSize( aList ) );

    searchTemplate->value = 9;
    dataSearch = ( data* ) searchOList( aList, searchTemplate );
    EX_INT_EQ( "Search end", 9, dataSearch->value );

    searchTemplate->value = -77;
    dataSearch = ( data* ) searchOList( aList, searchTemplate );
    EX_INT_EQ( "Search begin", -77, dataSearch->value );

    searchTemplate->value = 9;
    removeInOrder( aList, searchTemplate );
    EX_STR_EQ( "Remove end", "-77 - -9 - 7", result );
    EX_INT_EQ( "size--", 3, getOListSize( aList ) );

    searchTemplate->value = -77;
    removeInOrder( aList, searchTemplate );
    EX_STR_EQ( "First begin", "-9 - 7", result );
    EX_INT_EQ( "size--", 2, getOListSize( aList ) );

    searchTemplate->value = 10;
    EX_FALSE( "Delete Fail", removeInOrder( aList, searchTemplate ) );

    EX_FALSE( "before emptyOList", oListIsEmpty( aList ) );
    emptyOList( aList );
    EX_TRUE( "after emptyOList", oListIsEmpty( aList ) );

    deleteList( &aList );
    EX_NULL( "deleteList", aList );

    END_TESTS;
}