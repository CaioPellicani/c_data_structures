#include "../../src/order_linked_list.h"
#include "orderLinkedListTests.h"
#include "minunit.h"
#include "base_tests.h"

orderLinkedList* aList;

char* ollRefresh(){
    strcpy( result, "\0" );
    ollDataUse( aList, &showData );
    return result;
}

int runOrderLinkedListTest(){
    INIT_TESTS( "OrderLinkedList" );

    aList = ollInit( &comparison ); 
    EX_NOT_NULL( "ollInit", aList ); 

    ollInsert( aList, ( data* )newData( 6 ) );
    EX_STR_EQ( "First ollInsert", "6", ollRefresh() );
    EX_INT_EQ( "size++", 1, ollGetSize( aList ) );

    ollInsert( aList, ( data* )newData( 9 ) );
    EX_STR_EQ( "ollInsert", "6; 9", ollRefresh() );
    EX_INT_EQ( "size++", 2, ollGetSize( aList ) );

    ollInsert( aList, ( data* )newData( 7 ) );
    EX_STR_EQ( "ollInsert", "6; 7; 9", ollRefresh() );
    EX_INT_EQ( "size++", 3, ollGetSize( aList ) );

    ollInsert( aList, ( data* )newData( -77 ) );
    EX_STR_EQ( "ollInsert begin", "-77; 6; 7; 9", ollRefresh() );
    EX_INT_EQ( "size++", 4, ollGetSize( aList ) );

    searchTemplate->value = 6;
    dataSearch = ( data* ) ollSearch( aList, searchTemplate );
    EX_INT_EQ( "ollSearch middle", 6, dataSearch->value );

    searchTemplate->value = 5;
    dataSearch = ( data* ) ollSearch( aList, searchTemplate );
    EX_NULL( "Search fail", dataSearch );

    ollInsert( aList, ( data* )newData( -9 ) );
    EX_STR_EQ( "ollInsert end", "-77; -9; 6; 7; 9", ollRefresh() );
    EX_INT_EQ( "size++", 5, ollGetSize( aList ) );

    searchTemplate->value = 6;
    ollRemove( aList, searchTemplate );
    EX_STR_EQ( "First ollRemove middle", "-77; -9; 7; 9", ollRefresh() );
    EX_INT_EQ( "size--", 4, ollGetSize( aList ) );

    searchTemplate->value = 9;
    dataSearch = ( data* ) ollSearch( aList, searchTemplate );
    EX_INT_EQ( "ollSearch end", 9, dataSearch->value );

    searchTemplate->value = -77;
    dataSearch = ( data* ) ollSearch( aList, searchTemplate );
    EX_INT_EQ( "ollSearch begin", -77, dataSearch->value );

    searchTemplate->value = 9;
    ollRemove( aList, searchTemplate );
    EX_STR_EQ( "ollRemove end", "-77; -9; 7", ollRefresh() );
    EX_INT_EQ( "size--", 3, ollGetSize( aList ) );

    searchTemplate->value = -77;
    ollRemove( aList, searchTemplate );
    EX_STR_EQ( "ollRemove", "-9; 7", ollRefresh() );
    EX_INT_EQ( "size--", 2, ollGetSize( aList ) );

    searchTemplate->value = 10;
    EX_FALSE( "ollRemove Fail", ollRemove( aList, searchTemplate ) );

    EX_FALSE( "before ollEmptyList", ollIsEmpty( aList ) );
    ollEmptyList( aList );
    EX_TRUE( "after ollEmptyList", ollIsEmpty( aList ) );

    ollDelete( &aList );
    EX_NULL( "ollDelete", aList );

    END_TESTS;
}