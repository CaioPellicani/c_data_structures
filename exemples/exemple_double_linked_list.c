#include "../src/stdHeader.h"
#include "../src/double_linked_list.h"

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

int main( int argc, char** argv ){
    list* aList = NULL;

    aList = initList();

    for( int i = 0; i < 5; i++ ){
        pushTail( aList, ( data* )newData( i ) );
    }
    printf( "\n### PushTail       -> ");
    showList( aList, &showData );

    for( int i = 0; i < 5; i++ ){
        pushHead( aList, ( data* )newData( i ) );
    }
    printf( "\n### PushHead       -> ");
    showList( aList, &showData );  

    insertAt( aList, ( data* )newData( 32 ), 5 );
    printf( "\n### Insert at 5    -> ");
    showList( aList, &showData );

    removeAt( aList, 6 );
    printf( "\n### RemoveAt 6     -> " );
    showList( aList, &showData );

    popHead( aList );
    printf( "\n### PopHead        -> " );
    showList( aList, &showData );

    popTail( aList );
    printf( "\n### PopTail        -> " );
    showList( aList, &showData );

    emptyList( aList );
    printf( "\n### Empty the List -> ");
    showList( aList, &showData );

    deleteList( aList );
    
    return 0;
}

