#ifndef __CORE_SINGLE_CARDINAL_H__
#define __CORE_SINGLE_CARDINAL_H__

    #include "stdHeader.h"

    typedef void ( *dataUseFunction ) ( void* data );
    typedef struct node{
        void * data;
        struct node* nextNode;
    }node;

    bool insertInBetween( node** firstNode, int* size, void* _data, node* _prevNode );
    bool removeNextNode( node** firstNode, int* size, node* _prevNode );
    node* getNodeAt( node* firstNode, int position, bool insert, int size );
    void* getNodeData( node* firstNode, int position, int size );
    bool dataUse( node* firstNode, dataUseFunction dataUseFunc );

#endif