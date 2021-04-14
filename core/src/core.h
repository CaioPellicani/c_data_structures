#ifndef __CORE_H__
#define __CORE_H__

    #include "stdHeader.h"

    typedef struct node{
        void * data;
        struct node* nextNode;
    }node;

    node* newBlankNode();
    bool insertInBetween( node** firstNode, int* size, void* _data, node* _prevNode );
    bool removeNextNode( node** firstNode, int* size, node* _prevNode );
    node* getNodeAt( node* firstNode, int position, char* from, int size );

#endif