#include "../../src/linked_list.h"
#include "minunit.h"
#include "base_tests.h"

linkedList* aList;

char* llRefresh(){
    strcpy( result, "\0" );
    llDataUse( aList, &showData );
    return result;
}

int runLinkedListTest(){
    INIT_TESTS( "LinkedList" );

    data* dataAt = NULL;
    aList = llInit();
    EX_NOT_NULL( "llInit", aList ); 

    llPushHead( aList, ( data* )newData( 1 ) );
    EX_STR_EQ( "First llPushHead", "1", llRefresh() );
    EX_INT_EQ( "size++", 1, llGetSize( aList ) );

    llPushTail( aList, ( data* )newData( 1 ) );
    EX_STR_EQ( "First llPushTail", "1; 1", llRefresh() );
    EX_INT_EQ( "size++", 2, llGetSize( aList ) );
    
    llInsertAt( aList, ( data* )newData( 5 ), 1 );
    EX_STR_EQ( "llInsertAt 1", "1; 5; 1", llRefresh() );
    EX_INT_EQ( "size++", 3, llGetSize( aList ) );

    llInsertAt( aList, ( data* )newData( 10 ), 3 );
    EX_STR_EQ( "llInsertAt 3", "1; 5; 1; 10", llRefresh() );
    EX_INT_EQ( "size++", 4, llGetSize( aList ) );
  
    dataAt = ( data* ) llGetDataAt( aList, 1 );
    EX_INT_EQ( "llGetDataAt 1", 5, dataAt->value );
    EX_NOT_NULL( "llGetDataAt not null", dataAt );

    dataAt = ( data* ) llGetHeadData( aList );;
    EX_INT_EQ( "llGetHeadData", 1, dataAt->value );

    dataAt = ( data* ) llGetTailData( aList );;
    EX_INT_EQ( "llGetTailData", 10, dataAt->value );

    dataAt = ( data* ) llGetDataAt( aList, 100 );
    EX_NULL( "llGetDataAt fail", dataAt );

    llInsertAt( aList, ( data* )newData( 9 ), 0 );
    EX_STR_EQ( "llInsertAt 0", "9; 1; 5; 1; 10", llRefresh() );
    EX_INT_EQ( "size++", 5, llGetSize( aList ) );

    llRemoveAt( aList, 1 );
    EX_STR_EQ( "llRemoveAt 1", "9; 5; 1; 10", llRefresh() );
    EX_INT_EQ( "size--", 4, llGetSize( aList ) );

    llPopHead( aList );
    EX_STR_EQ( "llPopHead", "5; 1; 10", llRefresh() );
    EX_INT_EQ( "size--", 3, llGetSize( aList ) );
    
    llPopTail( aList );
    EX_STR_EQ( "llPopTail", "5; 1", llRefresh() );
    EX_INT_EQ( "size--", 2, llGetSize( aList ) );
    
    EX_FALSE( "before llEmptyList", llIsEmpty( aList ) );
    llEmptyList( aList );
    EX_TRUE( "llEmptyList", llIsEmpty( aList ) );

    dataAt = ( data* ) llGetHeadData( aList );
    EX_NULL( "llGetHeadData fail", dataAt );

    dataAt = ( data* ) llGetTailData( aList );
    EX_NULL( "llGetTailData fail", dataAt );

    llDelete( &aList );
    EX_NULL( "llDelete", aList );
    END_TESTS;
}
