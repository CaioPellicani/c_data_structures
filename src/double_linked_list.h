#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include "../core/src/stdHeader.h"

typedef struct  strList doubleLinkedList;



doubleLinkedList* dllInit();
void dllDeleteList( doubleLinkedList** _list );

bool dllIsEmpty( doubleLinkedList* _list );
int dllGetSize( doubleLinkedList* _list );

bool dllPushHead( doubleLinkedList* _list, void* _data );
bool dllPushTail( doubleLinkedList* _list, void* _data );
bool dllInsertAt( doubleLinkedList* _list, void* _data, int pos );

bool dllPopHead( doubleLinkedList* _list );
bool dllPopTail( doubleLinkedList* _list );
bool dllRemoveAt( doubleLinkedList* _list, int pos );

void* dllGetDataAt( doubleLinkedList* _list, int pos );
bool dllDataUse( doubleLinkedList* _list, void (*showData) ( void* data) );

void dllEmptyList( doubleLinkedList* _list );

#endif