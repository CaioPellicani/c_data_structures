#include "../../src/binary_search_tree.h"
#include "minunit.h"
#include "base_tests.h"

binarySearchTree* aTree;

char* bstInorder(){
    strcpy( result, "\0" );
    bstInorderDataUse( aTree, &showData );
    return result;
}

char* bstPreorder(){
    strcpy( result, "\0" );
    bstPreorderDataUse( aTree, &showData );
    return result;
}
char* bstPostorder(){
    strcpy( result, "\0" );
    bstPostorderDataUse( aTree, &showData );
    return result;
}

int runBinarySearchTreeTest(){
    INIT_TESTS( "BinaryTree" );

    aTree = bstInit( &comparison );
    EX_NOT_NULL( "llInit", aTree );

    bstInsert( aTree, ( data* )newData(5) ); 
    EX_STR_EQ( "First bstInsert", "5", bstPreorder() );

    bstInsert( aTree, ( data* )newData(-10) );
    EX_STR_EQ( "bstInsert", "-10; 5", bstPreorder() );  

    dataSearch = ( data* ) bstGetBiggerData( aTree );
    EX_INT_EQ( "bstGetBiggerData", 5, dataSearch->value );  


    bstInsert( aTree, ( data* )newData(10) );
    EX_STR_EQ( "bstInsert", "-10; 5; 10", bstPreorder() );

    bstInsert( aTree, ( data* )newData(8) );

    dataSearch = ( data* ) bstGetLowerData( aTree );
    EX_INT_EQ( "bstGetLowerData", -10, dataSearch->value );

    dataSearch = ( data* ) bstGetBiggerData( aTree );
    EX_INT_EQ( "bstGetBiggerData", 10, dataSearch->value );

    bstInsert( aTree, ( data* )newData(-8) );
    EX_STR_EQ( "bstInsert", "-10; -8; 5; 8; 10", bstPreorder() );
    EX_STR_EQ( "bstInorder", "5; -10; -8; 10; 8", bstInorder() );
    EX_STR_EQ( "bstPostorder", "-8; -10; 8; 10; 5", bstPostorder() );
 
    bstInsert( aTree, ( data* )newData( -15 ) );
    bstInsert( aTree, ( data* )newData( 15 ) );
    bstInsert( aTree, ( data* )newData( 7 ) );
    bstInsert( aTree, ( data* )newData( -5 ) );   
    bstInsert( aTree, ( data* )newData( -4 ) );
    bstInsert( aTree, ( data* )newData( -6 ) );
    EX_STR_EQ( "bstInsert", "-15; -10; -8; -6; -5; -4; 5; 7; 8; 10; 15", bstPreorder() );   

    dataSearch = ( data* ) bstGetLowerData( aTree );
    EX_INT_EQ( "bstGetLowerData", -15, dataSearch->value );

    dataSearch = ( data* ) bstGetBiggerData( aTree );
    EX_INT_EQ( "bstGetBiggerData", 15, dataSearch->value );

    searchTemplate->value = 5;
    dataSearch = ( data* ) bstSearch( aTree, searchTemplate );
    EX_INT_EQ( "bstSearch mainRoot", 5, dataSearch->value );

    searchTemplate->value = -6;
    dataSearch = ( data* ) bstSearch( aTree, searchTemplate );
    EX_INT_EQ( "bstSearch -6", -6, dataSearch->value );

    searchTemplate->value = 8;
    dataSearch = ( data* ) bstSearch( aTree, searchTemplate );
    EX_INT_EQ( "bstSearch 8", 8, dataSearch->value );

    searchTemplate->value = 7;
    dataSearch = ( data* ) bstSearch( aTree, searchTemplate );
    EX_INT_EQ( "bstSearch 8", 7, dataSearch->value ); 

    searchTemplate->value = 11;
    dataSearch = ( data* ) bstSearch( aTree, searchTemplate );
    EX_NULL( "bstSearch fail", dataSearch );

    searchTemplate->value = -10;
    bstRemove( aTree, searchTemplate );
    EX_STR_EQ( "bstRemove middle", "-15; -8; -6; -5; -4; 5; 7; 8; 10; 15", bstPreorder() );

    searchTemplate->value = -10;
    dataSearch = ( data* ) bstSearch( aTree, searchTemplate );
    EX_NULL( "bstSearch fail", dataSearch );    

    searchTemplate->value = -4;
    bstRemove( aTree, searchTemplate );
    EX_STR_EQ( "bstRemove leave", "-15; -8; -6; -5; 5; 7; 8; 10; 15", bstPreorder() );

    searchTemplate->value = 5;
    bstRemove( aTree, searchTemplate );
    EX_STR_EQ( "bstRemove mainRoot", "-15; -8; -6; -5; 7; 8; 10; 15", bstPreorder() );

    searchTemplate->value = 5;
    EX_FALSE( "bstRemove fail", bstRemove( aTree, searchTemplate ) );

    EX_FALSE( "before btEmptyList", bstIsEmpty( aTree ) );
    bstEmptyTree( aTree );
    EX_TRUE( "after btEmptyList", bstIsEmpty( aTree ) );

    bstDelete( &aTree );
    EX_NULL( "bstDelete", aTree );

    END_TESTS;
}
