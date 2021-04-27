#include "../../src/linked_list.h"
#include "minunit.h"
#include "base_tests.h"

linkedList* aList;

void refreshLinkedList(){
    strcpy( result, "\0" );
    llDataUse( aList, &showData );
}

int runLinkedListTest(){
    INIT_TESTS( "LinkedList", refreshLinkedList );

    aList = llInit();
    EX_NOT_NULL( "llInit", aList ); 

    llPushHead( aList, ( data* )newData( 1 ) );
    EX_STR_EQ( "First llPushHead", "1", result );
    EX_INT_EQ( "size++", 1, llGetSize( aList ) );

    llPushTail( aList, ( data* )newData( 1 ) );
    EX_STR_EQ( "First llPushTail", "1 - 1", result );
    EX_INT_EQ( "size++", 2, llGetSize( aList ) );
    
    llInsertAt( aList, ( data* )newData( 5 ), 1 );
    EX_STR_EQ( "llInsertAt 1", "1 - 5 - 1", result );
    EX_INT_EQ( "size++", 3, llGetSize( aList ) );

    llInsertAt( aList, ( data* )newData( 10 ), 3 );
    EX_STR_EQ( "llInsertAt 3", "1 - 5 - 1 - 10", result );
    EX_INT_EQ( "size++", 4, llGetSize( aList ) );
  
    data* dataAt = ( data* ) llGetDataAt( aList, 1 );
    EX_INT_EQ( "llGetDataAt 1", 5, dataAt->value );

    llInsertAt( aList, ( data* )newData( 9 ), 0 );
    EX_STR_EQ( "llInsertAt 0", "9 - 1 - 5 - 1 - 10", result );
    EX_INT_EQ( "size++", 5, llGetSize( aList ) );

    llRemoveAt( aList, 1 );
    EX_STR_EQ( "llRemoveAt 1", "9 - 5 - 1 - 10", result );
    EX_INT_EQ( "size--", 4, llGetSize( aList ) );

    llPopHead( aList );
    EX_STR_EQ( "llPopHead", "5 - 1 - 10", result );
    EX_INT_EQ( "size--", 3, llGetSize( aList ) );
    
    llPopTail( aList );
    EX_STR_EQ( "llPopTail", "5 - 1", result );
    EX_INT_EQ( "size--", 2, llGetSize( aList ) );
    
    EX_FALSE( "before llEmptyList", llIsEmpty( aList ) );
    llEmptyList( aList );
    EX_TRUE( "llEmptyList", llIsEmpty( aList ) );

    llDelete( &aList );
    EX_NULL( "llDelete", aList );
    END_TESTS;
}
