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
    EX_NOT_NULL( "init", aList ); 

    pushHead( aList, ( data* )newData( 1 ) );
    EX_STR_EQ( "First PushHead", "1", result );
    EX_INT_EQ( "size++", 1, getListSize( aList ) );

    pushTail( aList, ( data* )newData( 1 ) );
    EX_STR_EQ( "First PushTail", "1 - 1", result );
    EX_INT_EQ( "size++", 2, getListSize( aList ) );
    
    insertAt( aList, ( data* )newData( 5 ), 1 );
    EX_STR_EQ( "Insert at 1", "1 - 5 - 1", result );
    EX_INT_EQ( "size++", 3, getListSize( aList ) );

    insertAt( aList, ( data* )newData( 10 ), 3 );
    EX_STR_EQ( "Insert at 3", "1 - 5 - 1 - 10", result );
    EX_INT_EQ( "size++", 4, getListSize( aList ) );
  
    data* dataAt = ( data* ) getDataAt( aList, 1 );
    EX_INT_EQ( "get Data At 1", 5, dataAt->value );

    insertAt( aList, ( data* )newData( 9 ), 0 );
    EX_STR_EQ( "Insert at 0", "9 - 1 - 5 - 1 - 10", result );
    EX_INT_EQ( "size++", 5, getListSize( aList ) );

    removeAt( aList, 1 );
    EX_STR_EQ( "Remove at 1", "9 - 5 - 1 - 10", result );
    EX_INT_EQ( "size--", 4, getListSize( aList ) );

    popHead( aList );
    EX_STR_EQ( "PopHead", "5 - 1 - 10", result );
    EX_INT_EQ( "size--", 3, getListSize( aList ) );
    
    popTail( aList );
    EX_STR_EQ( "PopHead", "5 - 1", result );
    EX_INT_EQ( "size--", 2, getListSize( aList ) );
    
    deleteList( aList );

    END_TESTS;
}
