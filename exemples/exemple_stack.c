#include "../src/stdHeader.h"
#include "../src/stack.h"

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
    stack* aStack = NULL;

    aStack = initStack();

    int i = 0;
    for( ; i < 5; i++ ){
        push( aStack, ( data* )newData( i ) );
        printf( "# Push: ");
        stackDataUse( aStack, &showData );
        printf( "\n" );
    }
    
    data* top = (data*)getTopData( aStack );
    printf( "\n# Top: %d\n\n", top->value );

    for( ; i > 1; i-- ){
        pop( aStack );
        printf( "# Pop: ");
        stackDataUse( aStack, &showData );
        printf( "\n" );
    }

    deleteStack( aStack );
    
    puts( "\n" );

    return 0;
}