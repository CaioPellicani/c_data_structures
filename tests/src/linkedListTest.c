#include "../../src/linked_list.h"
#include "minunit.h"
#include "base_tests.h"

linkedList* aList;

void refreshLinkedList(){
    strcpy( result, "\0" );
    listDataUse( aList, &showData );
}

int runLinkedListTest(){
    INIT_TESTS( "LinkedList", refreshLinkedList );

    aList = initLinkedList(); 

    pushHead( aList, ( data* )newData( 1 ) );
    EX_STR_EQ( "First PushHead", "1", result );

    pushTail( aList, ( data* )newData( 1 ) );
    EX_STR_EQ( "First PushTail", "1 - 1", result );
    
    insertAt( aList, ( data* )newData( 5 ), 1 );
    EX_STR_EQ( "Insert at 1", "1 - 5 - 1", result );

    insertAt( aList, ( data* )newData( 10 ), 3 );
    EX_STR_EQ( "Insert at 3", "1 - 5 - 1 - 10", result );
  
    data* dataAt = ( data* ) getDataAt( aList, 1 );
    EX_INT_EQ( "get Data At 1", 5, dataAt->value );

    insertAt( aList, ( data* )newData( 9 ), 0 );
    EX_STR_EQ( "Insert at 0", "9 - 1 - 5 - 1 - 10", result );

    removeAt( aList, 1 );
    EX_STR_EQ( "Remove at 1", "9 - 5 - 1 - 10", result );

    popHead( aList );
    EX_STR_EQ( "PopHead", "5 - 1 - 10", result );

    popTail( aList );
    EX_STR_EQ( "PopHead", "5 - 1", result );

    deleteList( aList );

    END_TESTS;
}
