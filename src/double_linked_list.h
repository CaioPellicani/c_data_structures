#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include "../core/src/stdHeader.h"

typedef struct  strList doubleList;



doubleList* initDList();
bool dllIsEmpty( doubleList* _list );
int getDListSize( doubleList* _list );

bool pushDLLHead( doubleList* _list, void* _data );
bool pushDLLTail( doubleList* _list, void* _data );
bool insertDLLAt( doubleList* _list, void* _data, int pos );

bool popDLLHead( doubleList* _list );
bool popDLLTail( doubleList* _list );
bool removeDLLAt( doubleList* _list, int pos );

void emptyDLL( doubleList* _list );
void* getDLLDataAt( doubleList* _list, int pos );

bool dllDataUse( doubleList* _list, void (*showData) ( void* data) );

void deleteDLL( doubleList** _list );

#endif