#include "../../src/stack.h"
#include "minunit.h"
#include "base_tests.h"

stack* aStack;

void refreshStack(){
    strcpy( result, "\0" );
    stackDataUse( aStack, &showData );
}

int runStackTest(){ 
    INIT_TESTS( "Stack", refreshStack );
    aStack = initStack();

    push( aStack, (data*)newData( 1 ) );
    push( aStack, (data*)newData( 2 ) );
    push( aStack, (data*)newData( 3 ) );

    EX_STR_EQ( "PUSH", "3 - 2 - 1", result ); 

    pop( aStack );

    data* top = (data*)getTopData( aStack );
    EX_INT_EQ( "Get Top of the Stack", 2, top->value );

    pop( aStack );

    EX_STR_EQ( "POP", "1", result );

    END_TESTS;
}