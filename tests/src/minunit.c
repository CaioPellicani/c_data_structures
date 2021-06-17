#include "minunit.h"

int closeTest( testGroup group ){
    free( *( group.template ) );
    return group.testsRun;
}
int testFailure( testGroup group, char* testName, char* file, int line, char* expect, char* get ){
    printf( "\nGroup: \033[33m%s\033[0m", group.name );  
    printf( "\nRun %d tests\n", group.testsRun );                
    printf( "\n\033[31mTEST \033[7m%s\033[0m \33[31mFAILED \033[0m", testName );
    printf( "-> in %s:%d\n", file, line ); 
    printf( "EXPECT -> %s\n", expect );     
    if( strcmp( get, "" ) != 0 ){  
        printf( "GET    -> %s\n", get );     
    }                    
    return closeTest( group );
}