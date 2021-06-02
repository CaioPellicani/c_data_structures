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
    EX_INT_EQ( "getSizeStack 0", 0, getSizeStack( aStack ) );

    push( aStack, (data*)newData( 1 ) );
    push( aStack, (data*)newData( 2 ) );
    push( aStack, (data*)newData( 3 ) );

    EX_STR_EQ( "PUSH", "3; 2; 1", refreshStack() ); 
    EX_INT_EQ( "getSizeStack +3", 3, getSizeStack( aStack ) );

    pop( aStack );

    data* top = (data*)getTopData( aStack );
    EX_INT_EQ( "Get Top of the Stack", 2, top->value );

    pop( aStack );
    EX_STR_EQ( "POP", "1", refreshStack() );
    EX_INT_EQ( "getSizeStack --", 1, getSizeStack( aStack ) );

    EX_FALSE( "before emptyStack", stackIsEmpty( aStack ) );
    emptyStack( aStack );
    EX_TRUE( "after emptyStack", stackIsEmpty( aStack ) );

    top = (data*)getTopData( aStack );
    EX_NULL( "Fail getTopData", top );

    deleteStack( &aStack );
    EX_NULL( "deleteStack", aStack );

    emptyStack( aStack ); //try access to a freed data

    END_TESTS;
}