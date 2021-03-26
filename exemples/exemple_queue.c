#include "../src/stdHeader.h"
#include "../src/queue.h"


typedef struct data{
    int value;
}data;

data* newData( int _value ){
    data* newData = ( data* ) malloc( sizeof( data ) );
    newData->value = _value;
    return newData;
}

void showData( void* _data ){
    data* aData = ( data* )_data;
    printf( "%d - ", aData->value );
}

int main(){
    queue* aQueue = NULL;

    aQueue = initQueue();

    int i = 0;
    for( ; i < 5; i++ ){
        push( aQueue, ( data* )newData( i ) );
        printf( "# Push: ");
        showQueue( aQueue, &showData );
        printf( "\n" );
    }
    
    data* end = (data*)getEndData( aQueue );
    printf( "\n# End: %d\n\n", end->value );

    for( ; i > 1; i-- ){
        pop( aQueue );
        printf( "# Pop: ");
        showQueue( aQueue, &showData );
        printf( "\n" );
    }
    printf( "\n" );

    emptyQueue( aQueue );
    printf( "\n### Empty the Queue ###\n");
    showQueue( aQueue, &showData );

    deleteQueue( aQueue );

    return 0;
}