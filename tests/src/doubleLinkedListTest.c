#include "../../src/double_linked_list.h"
#include "doubleLinkedListTest.h"
#include "minunit.h"
#include "base_tests.h"

doubleLinkedList* aList;

char* dllRefresh(){
    strcpy( result, "\0" );
    dllDataUse( aList, &showData );
    return result;
}

int runDoubleLinkedListTest(){
    INIT_TESTS( "DoubleLinkedList" ); 

    data* dataAt = NULL; 
    aList = dllInit(); 
    EX_NOT_NULL( "dllInit", aList );

    EX_INT_EQ( "dllGetSize 0", 0, dllGetSize( aList ) );

    dllPushHead( aList, ( data* )newData( 1 ) );
    EX_STR_EQ( "First dllPushHead", "1", dllRefresh() );
    EX_INT_EQ( "dllGetSize ++", 1, dllGetSize( aList ) );

    dllPushTail( aList, ( data* )newData( 1 ) );
    EX_STR_EQ( "First dllPushTail", "1; 1", dllRefresh() );
    EX_INT_EQ( "dllGetSize ++", 2, dllGetSize( aList ) );
    
    dllInsertAt( aList, ( data* )newData( 5 ), 1 );
    EX_STR_EQ( "dllInsertAt 1", "1; 5; 1", dllRefresh() );
    EX_INT_EQ( "dllGetSize ++", 3, dllGetSize( aList ) );

    dllInsertAt( aList, ( data* )newData( 10 ), 3 );
    EX_STR_EQ( "dllInsertAt 3", "1; 5; 1; 10", dllRefresh() );
    EX_INT_EQ( "size++", 4, dllGetSize( aList ) );
  
    dataAt = ( data* ) dllGetDataAt( aList, 1 );
    EX_INT_EQ( "get Data At 1", 5, dataAt->value );

    dataAt = ( data* ) dllGetHeadData( aList );;
    EX_INT_EQ( "dllGetHeadData", 1, dataAt->value );

    dataAt = ( data* ) dllGetTailData( aList );;
    EX_INT_EQ( "dllGetTailData", 10, dataAt->value );

    dllInsertAt( aList, ( data* )newData( 9 ), 0 );
    EX_STR_EQ( "dllInsertAt 0", "9; 1; 5; 1; 10", dllRefresh() );
    EX_INT_EQ( "dllGetSize ++", 5, dllGetSize( aList ) );

    dllRemoveAt( aList, 1 );
    EX_STR_EQ( "dllRemoveAt 1", "9; 5; 1; 10", dllRefresh() );
    EX_INT_EQ( "dllGetSize --", 4, dllGetSize( aList ) );

    dllPopHead( aList );
    EX_STR_EQ( "dllPopHead", "5; 1; 10", dllRefresh() );
    EX_INT_EQ( "dllGetSize --", 3, dllGetSize( aList ) );
    
    dllPopTail( aList );
    EX_STR_EQ( "dllPopTail", "5; 1", dllRefresh() );
    EX_INT_EQ( "dllGetSize --", 2, dllGetSize( aList ) );
    
    EX_FALSE( "before dllEmptyList", dllIsEmpty( aList ) );
    dllEmptyList( aList );
    EX_TRUE( "after dllEmptyList", dllIsEmpty( aList ) );

    dllDelete( &aList );
    EX_NULL( "dllDelete", aList );

    END_TESTS;
}