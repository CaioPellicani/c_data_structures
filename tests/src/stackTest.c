#include "../../src/stack.h"
#include "minunit.h"
#include "base_tests.h"

stack* aStack;

char* refreshStack(){
    strcpy( result, "\0" );
    stackDataUse( aStack, &showData );
    return result;
}

int runStackTest(){ 
    INIT_TESTS( "Stack" );
    aStack = initStack();
    EX_NOT_NULL( "init", aStack ); 

    push( aStack, (data*)newData( 1 ) );
    push( aStack, (data*)newData( 2 ) );
    push( aStack, (data*)newData( 3 ) );

    EX_STR_EQ( "PUSH", "3; 2; 1", refreshStack() ); 
    EX_INT_EQ( "size+3", 3, getSizeStack( aStack ) );

    pop( aStack );

    data* top = (data*)getTopData( aStack );
    EX_INT_EQ( "Get Top of the Stack", 2, top->value );

    pop( aStack );
    EX_STR_EQ( "POP", "1", refreshStack() );
    EX_INT_EQ( "size--", 1, getSizeStack( aStack ) );

    EX_FALSE( "before emptyStack", stackIsEmpty( aStack ) );
    emptyStack( aStack );
    EX_TRUE( "after emptyStack", stackIsEmpty( aStack ) );

    deleteStack( &aStack );
    EX_NULL( "deleteStack", aStack );

    END_TESTS;
}