#ifndef _BASE_TESTS_H_
#define _BASE_TESTS_H_

#include "../../core/src/stdHeader.h"

char result[500];

typedef struct data{
    int value;
    
}data;

data* newData( int _value ); 
void showData( void* _data );   
int comparison( void* _larger, void* _smaller );

data* searchTemplate;
data* dataSearch;

#endif