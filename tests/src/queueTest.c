#include "../../src/queue.h"
#include "minunit.h"
#include "base_tests.h"
queue* aQueue;

char* refreshQueue(){
    strcpy( result, "\0" );
    queueDataUse( aQueue, &showData );
    return result;
}

int runQueueTest(){
    INIT_TESTS( "Queue" );
    aQueue = initQueue();
    EX_NOT_NULL( "init", aQueue ); 
    EX_INT_EQ( "getSizeQueue 0", 0, getSizeQueue( aQueue ) );

    enqueue( aQueue, (data*)newData( 1 ) );
    EX_STR_EQ( "ENQUEUE", "1", refreshQueue() ); 
    EX_INT_EQ( "getSizeQueue ++", 1, getSizeQueue( aQueue ) );

    enqueue( aQueue, (data*)newData( 2 ) );
    EX_STR_EQ( "ENQUEUE", "2; 1", refreshQueue() ); 
    EX_INT_EQ( "getSizeQueue ++", 2, getSizeQueue( aQueue ) );

    enqueue( aQueue, (data*)newData( 3 ) );
    EX_STR_EQ( "ENQUEUE", "3; 2; 1", refreshQueue() ); 
    EX_INT_EQ( "getSizeQueue ++", 3, getSizeQueue( aQueue ) );

    dequeue( aQueue );

    EX_STR_EQ( "DEQUEUE", "3; 2", refreshQueue() );
    EX_INT_EQ( "getSizeQueue --", 2, getSizeQueue( aQueue ) );
    
    data* end = (data*)getEndData( aQueue );
    EX_INT_EQ( "Get End Of The Queue", 2, end->value );

    EX_FALSE( "before emptyQueue", queueIsEmpty( aQueue ) );
    emptyQueue( aQueue );
    EX_TRUE( "after emptyQueue", queueIsEmpty( aQueue ) );

    deleteQueue( &aQueue);
    EX_NULL( "deleteQueue", aQueue );

    emptyQueue( aQueue ); //try access to a freed data

    END_TESTS;
    return 0;
}