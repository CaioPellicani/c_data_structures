#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "../core/src/stdHeader.h"

typedef struct strLinkedList linkedList;

linkedList* initLinkedList();
bool isEmpty( linkedList* _list );
int getListSize( linkedList* _list );

void* getDataAt( linkedList* _list, int pos );
void* getHeadData( linkedList* _list );
void* getTailData( linkedList* _list );

bool pushHead( linkedList* _list, void* _data );
bool pushTail( linkedList* _list, void* _data );
bool insertAt( linkedList* _list, void* _data, int pos );

bool popHead( linkedList* _list );
bool popTail( linkedList* _list );
bool removeAt( linkedList* _list, int pos );

void emptyList( linkedList* _list );

bool listDataUse( linkedList* _list, void ( *dataUseFunction ) ( void* data) );

void deleteList( linkedList** _list );

#endif