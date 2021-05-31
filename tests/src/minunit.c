#include "minunit.h"

int closeTest( testGroup group ){
    free( *( group.template ) );
    return group.testsRun;
}
int testFailure( testGroup group, char* testName, char* expect, char* get ){
    printf( "\nGroup: \033[33m%s\033[0m", group.name );  
    printf( "\nRun %d tests\n", group.testsRun );                
    printf( "\n\033[31mTEST %s FAILED\n\033[0m", testName );
    printf( "EXPECT -> %s\n", expect );     
    if( strcmp( get, "" ) != 0 ){  
        printf( "GET -> %s\n", expect );     
    }                     
    return closeTest( group );
}