#include "base_tests.h"

data* newData( int _value ){
    data* newData = ( data* ) malloc( sizeof( data ) );
    newData->value = _value;
    return newData;
}   
void showData( void* _data ){
    data* aData = ( data* )_data;
    if( strcmp( result, "" ) == 0 ){
        sprintf( result, "%d", aData->value );
    }
    else{
        sprintf( result, "%s - %d", result, aData->value );
    }
}
