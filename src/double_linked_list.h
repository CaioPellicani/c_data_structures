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

bool pushHead( list* list, void* data );
bool pushTail( list* list, void* data );

bool popHead( list* list );
bool popTail( list* list );
void emptyList( list* list );

bool showList( list* list, void (*showData) ( void* data) );

void deleteList( list* list );

#endif