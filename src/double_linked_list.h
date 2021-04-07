#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include "stdHeader.h"

typedef struct  _list list;

list* initList();
bool isEmpty( list* _list );

bool pushHead( list* _list, void* _data );
bool pushTail( list* _list, void* _data );
bool insertAt( list* _list, void* _data, int pos );

bool popHead( list* _list );
bool popTail( list* _list );
bool removeAt( list* _list, int pos );

void emptyList( list* _list );
void* getDataAt( list* _list, int pos );

bool showList( list* _list, void (*showData) ( void* data) );

void deleteList( list* _list );

#endif