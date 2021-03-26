#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include "stdHeader.h"

#define MSG_NO_MEM "Not sufficient memory!\n"
#define MSG_NODEF_LIST "List is not defined!\n"
#define MSG_EMPTY_LIST "The List is Empty!\n"
#define MGS_OUT_RANGE(TYPE) "\n\nNot possible to %s. Position '%d' is out ouf range. Size of the List is '%d'\n", TYPE, pos, _list->size 

typedef struct node {
    void * data;
    struct node* nextNode;
    struct node* prevNode;
}node;

typedef struct{
    node * head;
    node * tail;
    int size;
}list;

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