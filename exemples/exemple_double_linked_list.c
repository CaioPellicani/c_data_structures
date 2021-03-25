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
    printf( "\n### Push Tail ###\n");
    showList( aList, &showData );

    for( int i = 0; i < 5; i++ ){
        pushHead( aList, ( data* )newData( i ) );
    }
    printf( "\n### Push Head ###\n");
    showList( aList, &showData );

    popHead( aList );
    popTail( aList );
    printf( "\n### Pop Head and Pop Tail ###\n");
    showList( aList, &showData );

    emptyList( aList );
    printf( "\n### Empty the List ###\n");
    showList( aList, &showData );

    deleteList( aList );
    
    return 0;
}

