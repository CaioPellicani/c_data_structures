#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include "stdHeader.h"

#define MSG_NO_MEM "Not sufficient memory!\n"
#define MSG_NODEF_LIST "List is not defined!\n"
#define MSG_EMPTY_LIST "The List is Empty!\n"

typedef struct node {
    void * data;
    struct node* nextNode;
    struct node* prevNode;
}node;

typedef struct{
    node * head;
    node * tail;
}list;

list* initList();

bool pushHead( list* _list, void* _data );
bool pushTail( list* _list, void* _data );

bool popHead( list* _list );
bool popTail( list* _list );
void emptyList( list* _list );

bool showList( list* _list, void (*showData) ( void* data) );

void deleteList( list* _list );

#endif