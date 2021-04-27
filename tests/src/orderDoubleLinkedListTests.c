#include "../../src/order_double_linked_list.h"
#include "orderDoubleLinkedListTests.h"
#include "minunit.h"
#include "base_tests.h"

orderDoubleLinkedList* aList;

void refreshOrderDoubleLinkedList(){
    strcpy( result, "\0" );
    odllDataUse( aList, &showData );
}

int runOrderDoubleLinkedListTest(){
    INIT_TESTS( "OrderDoubleLinkedList", refreshOrderDoubleLinkedList );
    aList = odllInit( &comparison ); 
    EX_NOT_NULL( "odllInit", aList ); 

    odllInsert( aList, ( data* )newData( 6 ) );
    EX_STR_EQ( "First odllInsert", "6", result );
    EX_INT_EQ( "size++", 1, odllGetSize( aList ) );

    odllInsert( aList, ( data* )newData( 9 ) );
    EX_STR_EQ( "odllInsert", "6 - 9", result );
    EX_INT_EQ( "size++", 2, odllGetSize( aList ) );

    odllInsert( aList, ( data* )newData( 7 ) );
    EX_STR_EQ( "odllInsert", "6 - 7 - 9", result );
    EX_INT_EQ( "size++", 3, odllGetSize( aList ) );

    odllInsert( aList, ( data* )newData( -77 ) );
    EX_STR_EQ( "odllInsert begin", "-77 - 6 - 7 - 9", result );
    EX_INT_EQ( "size++", 4, odllGetSize( aList ) );

    data* searchTemplate = newData( 6 );
    data* dataSearch = ( data* ) odllSearch( aList, searchTemplate );
    EX_INT_EQ( "odllSearch middle", 6, dataSearch->value );

    searchTemplate->value = 5;
    dataSearch = ( data* ) odllSearch( aList, searchTemplate );
    EX_NULL( "Search fail", dataSearch );

    odllInsert( aList, ( data* )newData( -9 ) );
    EX_STR_EQ( "odllInsert end", "-77 - -9 - 6 - 7 - 9", result );
    EX_INT_EQ( "size++", 5, odllGetSize( aList ) );

    searchTemplate->value = 6;
    odllRemove( aList, searchTemplate );
    EX_STR_EQ( "First odllRemove middle", "-77 - -9 - 7 - 9", result );
    EX_INT_EQ( "size--", 4, odllGetSize( aList ) );

    searchTemplate->value = 9;
    dataSearch = ( data* ) odllSearch( aList, searchTemplate );
    EX_INT_EQ( "odllSearch end", 9, dataSearch->value );

    searchTemplate->value = -77;
    dataSearch = ( data* ) odllSearch( aList, searchTemplate );
    EX_INT_EQ( "odllSearch begin", -77, dataSearch->value );

    searchTemplate->value = 9;
    odllRemove( aList, searchTemplate );
    EX_STR_EQ( "odllRemove end", "-77 - -9 - 7", result );
    EX_INT_EQ( "size--", 3, odllGetSize( aList ) );

    searchTemplate->value = -77;
    odllRemove( aList, searchTemplate );
    EX_STR_EQ( "odllRemove", "-9 - 7", result );
    EX_INT_EQ( "size--", 2, odllGetSize( aList ) );

    searchTemplate->value = 10;
    EX_FALSE( "odllRemove Fail", odllRemove( aList, searchTemplate ) );

    EX_FALSE( "before odllEmptyList", odllIsEmpty( aList ) );
    odllEmptyList( aList );
    EX_TRUE( "after odllEmptyList", odllIsEmpty( aList ) );

    odllDelete( &aList );
    EX_NULL( "odllDelete", aList );

    END_TESTS;
}