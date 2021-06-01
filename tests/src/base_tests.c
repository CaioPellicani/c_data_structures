#include "base_tests.h"

data* newData( int _value ){
    data* newData = ( typeof( newData ) ) malloc( sizeof( *newData ) );
    newData->value = _value;
    return newData;
}   
void showData( void* _data ){
    data* aData = ( typeof( aData ) )_data;
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
    data *larger = ( typeof( larger ) ) _larger;
    data *smaller = ( typeof( smaller ) ) _smaller;

    if( larger->value == smaller->value ){
        return EQUAL;
    }

    if( larger->value >= smaller->value ){
        return LARGER;
    }
    return SMALLER;
}
