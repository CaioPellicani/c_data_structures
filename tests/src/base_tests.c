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

bool comparison( void* _larger, void* _smaller ){
    data *larger = ( data*)_larger;
    data *smaller = ( data* ) _smaller;

    if( larger->value >= smaller->value ){
        return true;
    }
    return false;
}
