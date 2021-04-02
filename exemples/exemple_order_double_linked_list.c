#include "../src/stdHeader.h"
#include "../src/order_double_linked_list.h"

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

bool comparison( void* _larger, void* _smaller ){
    data *larger = ( data*)_larger;
    data *smaller = ( data* ) _smaller;

    if( larger->value >= smaller->value ){
        return true;
    }
    return false;
}

int main( int argc, char** argv ){
    orderList* aList = initOrderList( &comparison );

    insertInOrder( aList, newData(20) );
    insertInOrder( aList, newData(10) );  
    insertInOrder( aList, newData(5) );  
    insertInOrder( aList, newData(15) );
    insertInOrder( aList, newData(9) );
    insertInOrder( aList, newData(22) );
    insertInOrder( aList, newData(21) );

    printf( "\nList Data -> " );
    showOrderList( aList, showData );
    printf( "\n" );

    return 0;
}