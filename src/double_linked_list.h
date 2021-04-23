#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include "../core/src/stdHeader.h"

typedef struct  strList doubleList;



doubleList* _initList();
bool _isEmpty( doubleList* _list );
int getDListSize( doubleList* _list );

bool _pushHead( doubleList* _list, void* _data );
bool _pushTail( doubleList* _list, void* _data );
bool _insertAt( doubleList* _list, void* _data, int pos );

bool _popHead( doubleList* _list );
bool _popTail( doubleList* _list );
bool _removeAt( doubleList* _list, int pos );

void _emptyList( doubleList* _list );
void* _getDataAt( doubleList* _list, int pos );

bool _showList( doubleList* _list, void (*showData) ( void* data) );

void _deleteList( doubleList** _list );

#endif