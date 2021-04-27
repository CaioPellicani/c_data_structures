#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "../core/src/stdHeader.h"

typedef struct strLinkedList linkedList;

linkedList* llInit();
void llDelete( linkedList** _list );

bool llIsEmpty( linkedList* _list );
int llGetSize( linkedList* _list );

void* llGetDataAt( linkedList* _list, int pos );
void* llGetHeadData( linkedList* _list );
void* llGetTailData( linkedList* _list );

bool llPushHead( linkedList* _list, void* _data );
bool llPushTail( linkedList* _list, void* _data );
bool llInsertAt( linkedList* _list, void* _data, int pos );

bool llPopHead( linkedList* _list );
bool llPopTail( linkedList* _list );
bool llRemoveAt( linkedList* _list, int pos );

void llEmptyList( linkedList* _list );

bool llDataUse( linkedList* _list, void ( *dataUseFunction ) ( void* data) );


#endif