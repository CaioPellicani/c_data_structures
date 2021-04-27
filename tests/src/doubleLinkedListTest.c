#include "../../src/double_linked_list.h"
#include "doubleLinkedListTest.h"
#include "minunit.h"
#include "base_tests.h"

doubleList* aList;

void refreshDoubleLinkedList(){
    strcpy( result, "\0" );
    dllDataUse( aList, &showData );
}

int runDoubleLinkedListTest(){
    INIT_TESTS( "DoubleLinkedList", refreshDoubleLinkedList );  
    aList = initDList(); 
    EX_NOT_NULL( "init", aList );

    pushDLLHead( aList, ( data* )newData( 1 ) );
    EX_STR_EQ( "First PushHead", "1", result );
    EX_INT_EQ( "size++", 1, getDListSize( aList ) );

    pushDLLTail( aList, ( data* )newData( 1 ) );
    EX_STR_EQ( "First PushTail", "1 - 1", result );
    EX_INT_EQ( "size++", 2, getDListSize( aList ) );
    
    insertDLLAt( aList, ( data* )newData( 5 ), 1 );
    EX_STR_EQ( "Insert at 1", "1 - 5 - 1", result );
    EX_INT_EQ( "size++", 3, getDListSize( aList ) );

    insertDLLAt( aList, ( data* )newData( 10 ), 3 );
    EX_STR_EQ( "Insert at 3", "1 - 5 - 1 - 10", result );
    EX_INT_EQ( "size++", 4, getDListSize( aList ) );
  
    data* dataAt = ( data* ) getDLLDataAt( aList, 1 );
    EX_INT_EQ( "get Data At 1", 5, dataAt->value );

    insertDLLAt( aList, ( data* )newData( 9 ), 0 );
    EX_STR_EQ( "Insert at 0", "9 - 1 - 5 - 1 - 10", result );
    EX_INT_EQ( "size++", 5, getDListSize( aList ) );

    removeDLLAt( aList, 1 );
    EX_STR_EQ( "Remove at 1", "9 - 5 - 1 - 10", result );
    EX_INT_EQ( "size--", 4, getDListSize( aList ) );

    popDLLHead( aList );
    EX_STR_EQ( "PopHead", "5 - 1 - 10", result );
    EX_INT_EQ( "size--", 3, getDListSize( aList ) );
    
    popDLLTail( aList );
    EX_STR_EQ( "PopHead", "5 - 1", result );
    EX_INT_EQ( "size--", 2, getDListSize( aList ) );
    
    EX_FALSE( "before emptyList", dllIsEmpty( aList ) );
    emptyDLL( aList );
    EX_TRUE( "after emptyList", dllIsEmpty( aList ) );

    deleteDLL( &aList );
    EX_NULL( "deleteList", aList );

    END_TESTS;
}