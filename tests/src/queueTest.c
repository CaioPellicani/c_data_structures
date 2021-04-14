#include "../../src/queue.h"
#include "minunit.h"
#include "base_tests.h"
queue* aQueue;

void refreshQueue(){
    strcpy( result, "\0" );
    queueDataUse( aQueue, &showData );
}

int runQueueTest(){
    INIT_TESTS( "Queue", refreshQueue );
    aQueue = initQueue();

    enqueue( aQueue, (data*)newData( 1 ) );
    enqueue( aQueue, (data*)newData( 2 ) );
    enqueue( aQueue, (data*)newData( 3 ) );

    EX_STR_EQ( "ENQUEUE", "3 - 2 - 1", result ); 
    EX_INT_EQ( "size+3", 3, getSizeQueue( aQueue ) );

    dequeue( aQueue );

    EX_STR_EQ( "DEQUEUE", "3 - 2", result );
    EX_INT_EQ( "size--", 2, getSizeQueue( aQueue ) );
    
    data* end = (data*)getEndData( aQueue );
    EX_INT_EQ( "Get End Of The Queue", 2, end->value );

    END_TESTS;
    return 0;
}