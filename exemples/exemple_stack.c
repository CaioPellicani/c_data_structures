#include "../src/stdHeader.h"
#include "../src/stack.h"

typedef struct data{
    int value;
}data;

data* newData( int value ){
    data* newData = ( data* ) malloc( sizeof( data ) );
    newData->value = value;
    return newData;
}

void showData( data* data ){
    printf( "%d - ", data->value );
}

int main(){
    stack* aStack = NULL;

    aStack = initStack();
    int i = 0;

    for( i ; i < 5; i++ ){
        push( aStack, ( data* )newData( i ) );
        printf( "# Push: ");
        showStack( aStack, &showData );
        printf( "\n" );
    }
    printf( "\n" );

    for( i ; i > 1; i-- ){
        pop( aStack );
        printf( "# Pop: ");
        showStack( aStack, &showData );
        printf( "\n" );
    }
    printf( "\n" );

    emptyStack( aStack );
    printf( "\n### Empty the Stack ###\n");
    showStack( aStack, &showData );

    deleteStack( aStack );

    return 0;
}