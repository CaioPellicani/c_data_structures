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
node* getNodeAt( list* _list, int pos );

bool showList( list* _list, void (*showData) ( void* data) );

void deleteList( list* _list );

#endif