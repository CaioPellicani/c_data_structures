#include "../src/stdHeader.h"
#include "../src/linked_list.h"

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
    linkedList* aList = NULL;

    aList = initList();

    printf( "\n### PushHead       -> ");
    for( int i = 0; i < 5; i++ ){
        pushHead( aList, ( data* )newData( i ) );
    }
    listDataUse( aList, &showData );  

    printf( "\n### Insert at 0    -> ");
    insertAt( aList, ( data* )newData( 32 ), 0 );
    listDataUse( aList, &showData );

    printf( "\n### Insert at End  -> ");
    insertAt( aList, ( data* )newData( 35 ), getListSize( aList ) );
    listDataUse( aList, &showData );

    printf( "\n### PushTail       -> ");
    pushTail( aList, ( data* )newData( 48 ) );
    listDataUse( aList, &showData );

    data* dataAt = ( data* ) getDataAt( aList, 2 );
    printf( "\n### Data At Node 2 -> '%d'", dataAt->value );

    printf( "\n### RemoveAt 2     -> " );
    removeAt( aList, 2 );
    listDataUse( aList, &showData );

    printf( "\n### PopHead        -> " );
    popHead( aList );
    listDataUse( aList, &showData );

    dataAt = ( data* ) getDataAt( aList, 0 );
    printf( "\n### Data At 0      -> '%d'", dataAt->value );

    dataAt = ( data* ) getHeadData( aList );
    printf( "\n### Data At Head   -> '%d'", dataAt->value );

    printf( "\n### RemoveAt 0     -> " );
    removeAt( aList, 0 );
    listDataUse( aList, &showData );


    dataAt = ( data* ) getDataAt( aList, getListSize( aList ) - 1 );
    printf( "\n### Data At End    -> '%d'", dataAt->value );

    dataAt = ( data* ) getTailData( aList );
    printf( "\n### Data Tail      -> '%d'", dataAt->value );

    printf( "\n### RemoveAt End   -> " );
    removeAt( aList, getListSize( aList ) - 1 );
    listDataUse( aList, &showData );

    printf( "\n### PopTail        -> " );
    popTail( aList );
    listDataUse( aList, &showData );


    deleteList( aList );

    puts( "\n" );
    
    return 0;
}

