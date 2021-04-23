
#include "doubleLinkedListTest.h"
#include "minunit.h"
#include "base_tests.h"

doubleList* aList;

void refreshDoubleLinkedList(){
    strcpy( result, "\0" );
    _showList( aList, &showData );
}

int runDoubleLinkedListTest(){
    INIT_TESTS( "DoubleLinkedList", refreshDoubleLinkedList );  
    aList = _initList(); 
    EX_NOT_NULL( "init", aList );

    _pushHead( aList, ( data* )newData( 1 ) );
    EX_STR_EQ( "First PushHead", "1", result );
    EX_INT_EQ( "size++", 1, getDListSize( aList ) );

    _pushTail( aList, ( data* )newData( 1 ) );
    EX_STR_EQ( "First PushTail", "1 - 1", result );
    EX_INT_EQ( "size++", 2, getDListSize( aList ) );
    
    _insertAt( aList, ( data* )newData( 5 ), 1 );
    EX_STR_EQ( "Insert at 1", "1 - 5 - 1", result );
    EX_INT_EQ( "size++", 3, getDListSize( aList ) );

    _insertAt( aList, ( data* )newData( 10 ), 3 );
    EX_STR_EQ( "Insert at 3", "1 - 5 - 1 - 10", result );
    EX_INT_EQ( "size++", 4, getDListSize( aList ) );
  
    data* dataAt = ( data* ) _getDataAt( aList, 1 );
    EX_INT_EQ( "get Data At 1", 5, dataAt->value );

    _insertAt( aList, ( data* )newData( 9 ), 0 );
    EX_STR_EQ( "Insert at 0", "9 - 1 - 5 - 1 - 10", result );
    EX_INT_EQ( "size++", 5, getDListSize( aList ) );

    _removeAt( aList, 1 );
    EX_STR_EQ( "Remove at 1", "9 - 5 - 1 - 10", result );
    EX_INT_EQ( "size--", 4, getDListSize( aList ) );

    _popHead( aList );
    EX_STR_EQ( "PopHead", "5 - 1 - 10", result );
    EX_INT_EQ( "size--", 3, getDListSize( aList ) );
    
    _popTail( aList );
    EX_STR_EQ( "PopHead", "5 - 1", result );
    EX_INT_EQ( "size--", 2, getDListSize( aList ) );
    
    deleteList( aList );

    END_TESTS;
}