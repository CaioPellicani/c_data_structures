#include "base_tests.h"

data* newData( int _value ){
    data* newData = ( data* ) malloc( sizeof( *newData ) );
    newData->value = _value;
    return newData;
}   
void showData( void* _data ){
    data* aData = ( data* )_data;
    char buf[10];
    sprintf( buf, "%d", aData->value );
    
    if( strcmp( result, "" ) == 0 ){
        strcpy( result, buf );
    }
    else{
        strcat( result, "; " );
        strcat( result, buf );
    }
}

int comparison( void* _larger, void* _smaller ){
    data *larger = ( data* ) _larger;
    data *smaller = ( data* ) _smaller;

    if( larger->value == smaller->value ){
        return EQUAL;
    }

    if( larger->value >= smaller->value ){
        return LARGER;
    }
    return SMALLER;
}
