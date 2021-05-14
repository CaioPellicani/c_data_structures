#ifndef _STD_HEADER_H_
#define _STD_HEADER_H_

#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void die(const char *fmt, ...);

enum{ SMALLER, LARGER, EQUAL };

/* DEBUG */
typedef struct  strDebugData{
    int value;
}dData;

#define VAR_NAME(name) #name
#define DEBUG_DATA( data ) printf( "\n\t%s - %d\n", #data, getData( data ) );
int getData( void *dData );

/* END DEBUG */

#endif