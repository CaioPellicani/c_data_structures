#ifndef _BASE_TESTS_H_
#define _BASE_TESTS_H_

#include "../../core/src/stdHeader.h"

#define RESULT_SIZE 500
char result[RESULT_SIZE];

typedef struct data{
    int value;
}data;

data* newData( int _value ); 
void showData( void* _data );   
int comparison( void* _larger, void* _smaller );

data* searchTemplate;
data* dataSearch;

#endif